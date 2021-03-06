/************************************************************************
**
**  Copyright (c) Digital Equipment Corporation, 1990 All Rights Reserved.
**  Unpublished rights reserved under the copyright laws of the United States.
**  The software contained on this media is proprietary to and embodies the
**  confidential technology of Digital Equipment Corporation.  Possession, use,
**  duplication or dissemination of the software and media is authorized only
**  pursuant to a valid written license from Digital Equipment Corporation.
**  RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure by the U.S.
**  Government is subject to restrictions as set forth in Subparagraph
**  (c)(1)(ii) of DFARS 252.227-7013, or in FAR 52.227-19, as applicable.
**/

/************************************************************************
**
**  FACILITY:
**
**      Image Processing Services
**
**  ABSTRACT:
**
**      This module contains the user level service and support routines
**	for logical operations on two input images of bitonal data types
**      and generates a destination image of the bitonal data type as 
**      well.
**
**  ENVIRONMENT:
**
**      VAX/VMS, VAX/ULTRIX, RISC/ULTRIX
**
**  AUTHOR(S):
**
**      Karen Rodwell
**
**  CREATION DATE:
**
**      2-MAY-1990
**
************************************************************************/

/*
**  Table of contents
*/
#ifdef NODAS_PROTO
long _IpsLogicalBitonal();	                      /* main entry routine */
long _IpsLogicalCombine();	            /* handles call to combine bits */
#ifdef VMS
long _IpsLogicalCombineBits();		               /* use macro for VMS */
#endif
#endif

/*
**  Local routines
*/
long _BufferCombineBitonal();       /* c version combine buffers for ultrix */
void _DoBits();      /* handle odd unaligned bits of buffers to be combined */

/*
**  Include files
*/
#include <IpsDef.h>			    /* Ips Image Definitions	     */
#include <IpsMacros.h>			    /* Ips Macro Definitions	     */
#include <IpsMemoryTable.h>                 /* Ips Memory Mgt Functions      */
#ifndef NODAS_PROTO
#include <ipsprot.h>			    /* IPS Prototypes		    */
#endif
#include <IpsStatusCodes.h>		    /* Ips Status Codes		     */

/* flag to indicate memory was allocated here */
#if (defined(VAXC) && !defined(ALPHA) && !defined(__alpha))
static noshare unsigned long mem_allocated; 
#else
unsigned long mem_allocated; 
#endif
  
/*
**  External references
*/
#ifdef NODAS_PROTO
long _IpsBuildDstUdp();                            /* from ips__udp_utils.c */
long _IpsCopy();                                          /* from IPS__COPY */
#endif

/*****************************************************************************
**  _IpsLogicalBitonal - 
**
**  FUNCTIONAL DESCRIPTION:
**	Performs logic operations on corresponding values from the 
**      two source images to produce results for the destination image on 
**      a point by point basis.  
**
**  FORMAL PARAMETERS:
**
**      src1_udp    -- Pointer to first source udp
**	src2_udp    -- Pointer to second source udp
**	dst_udp     -- Pointer to destination udp (uninitialized)
**      cpp	    -- Control Processing Plane
**	operator    -- Logical operation to be performed on two planes
**
**  IMPLICIT INPUTS:  none
**  IMPLICIT OUTPUTS: none
**  FUNCTION VALUE:   none
**  SIGNAL CODES:     none
**  SIDE EFFECTS:     none
**
************************************************************************/
long _IpsLogicalBitonal(src1_udp, src2_udp, dst_udp, cpp, operator)
struct UDP *src1_udp;      /* First Source UDP for the logical operation  */
struct UDP *src2_udp;      /* Second Source UDP for the logical operation */
struct UDP *dst_udp;       /* Destination UDP generated by logic op       */ 
struct UDP *cpp;           /* Control Processsing plane for logic op      */
unsigned long operator;	   /* Function operator flag                      */
{
long status;
   
if ((operator < IpsK_LogicalMin) || (operator > IpsK_LogicalMax))
    return (IpsX_INVDARG);

if  (src1_udp->UdpB_Class != UdpK_ClassUBA)
    return (IpsX_UNSOPTION);

/* return mismatch error if the dimensions are mismatched */

if ((src1_udp->UdpL_ScnCnt != src2_udp->UdpL_ScnCnt) ||
    (src1_udp->UdpL_PxlPerScn != src2_udp->UdpL_PxlPerScn) ||
    (src1_udp->UdpB_DType != src2_udp->UdpB_DType))
    return (IpsX_NOMATCH); 

if ((src1_udp->UdpB_DType != UdpK_DTypeVU) || 
    (src2_udp->UdpB_DType != UdpK_DTypeVU))
    return (IpsX_INVDTYPE);

if (dst_udp->UdpA_Base == 0)
    mem_allocated = TRUE;
else
    mem_allocated = FALSE;

status = _IpsBuildDstUdp (src1_udp, dst_udp, 0, IpsM_RetainSrcDim, 
			IpsK_InPlaceAllowed);
if (status != IpsX_SUCCESS) return (status);

switch (src1_udp->UdpB_DType)
    {
    case UdpK_DTypeVU:
	return (_IpsLogicalCombine(src1_udp, src2_udp, dst_udp, cpp, operator));
    case UdpK_DTypeBU:
    case UdpK_DTypeWU:
    case UdpK_DTypeF:
    case UdpK_DTypeLU: 
    default:
        if (mem_allocated == TRUE)
            (*IpsA_MemoryTable[IpsK_FreeDataPlane])
			    (dst_udp->UdpA_Base);
        return (IpsX_INVDTYPE);
        break;
    };  /* end switch on DType */
return (IpsX_SUCCESS);
}

/*****************************************************************************
**  _IpsLogicalCombine - 
**
**  FUNCTIONAL DESCRIPTION:
**	Performs logic operations on corresponding values from the 
**      two bitonal source images to produce results for the bitonal
**      destination image on a point by point basis.  
**
**  FORMAL PARAMETERS:
**
**      src1_udp    -- Pointer to first source udp.
**	src2_udp    -- Pointer to second source udp.
**	dst_udp     -- Pointer to destination udp.
**      cpp	    -- Control Processing Plane.
**	operator    -- Arithmetic operation to be performed.
**
**  IMPLICIT INPUTS:  none
**  IMPLICIT OUTPUTS: none
**  FUNCTION VALUE:   none
**  SIGNAL CODES:     none
**  SIDE EFFECTS:     none
**
************************************************************************/
long _IpsLogicalCombine(src1_udp,src2_udp,dst_udp,cpp,operator)
struct UDP *src1_udp;      /* first source udp  */
struct UDP *src2_udp;      /* second source udp */
struct UDP *dst_udp;       /* destination udp   */
struct UDP *cpp;	   /* control processing plane */
unsigned long operator;    /* type of operation to be performed   */
{
struct UDP tmp_dst_udp;       /* tmp destination udp   */
long tmp_offset;
long status;

long scanline_count;
long scanline;
long src1_offset;
long src2_offset;
long dst_offset;
long bit_count;

scanline_count = src1_udp->UdpL_ScnCnt;
src1_offset = src1_udp->UdpL_Pos + (src1_udp->UdpL_X1 * 
    src1_udp->UdpL_PxlStride) + (src1_udp->UdpL_ScnStride * src1_udp->UdpL_Y1);
src2_offset = src2_udp->UdpL_Pos + (src2_udp->UdpL_X1 * 
    src2_udp->UdpL_PxlStride) + (src2_udp->UdpL_ScnStride * src2_udp->UdpL_Y1);
dst_offset = dst_udp->UdpL_Pos + (dst_udp->UdpL_X1 * 
    dst_udp->UdpL_PxlStride) + (dst_udp->UdpL_ScnStride * dst_udp->UdpL_Y1);
bit_count = src1_udp->UdpL_PxlPerScn * src1_udp->UdpL_PxlStride;

#ifdef VMS
for (scanline = 0;  scanline < scanline_count; scanline++)
    {
    _IpsLogicalCombineBits(
           bit_count,                             /* Bit count          */
           src1_offset,                           /* src1 bit offset     */
           src1_udp->UdpA_Base,                   /* buffer address */
           src2_offset,                           /* bit offset     */
           src2_udp->UdpA_Base,                   /* buffer address */
           dst_offset,                            /* bit offset     */
           dst_udp->UdpA_Base,                    /* buffer adr     */
           operator);
    src1_offset += src1_udp->UdpL_ScnStride;
    src2_offset += src2_udp->UdpL_ScnStride;
    dst_offset += dst_udp->UdpL_ScnStride;
    }
#else
    /*
    ** On non-VMS platforms
    */
    if (mem_allocated != TRUE)
        {
        /*
        ** When ther is a user defined dst buffer we must:
        ** Allocate zero buffer since GET_BITS and PUT_BITS does an
        ** exclusive "or".  Do the operation to this tmp buffer and
       ** copy to user buffer
        */
        tmp_dst_udp = *dst_udp;
        tmp_dst_udp.UdpA_Base = (*IpsA_MemoryTable[IpsK_AllocateDataPlane])
            (dst_udp->UdpL_ArSize>>3, IpsM_InitMem, 0);
        if (!tmp_dst_udp.UdpA_Base)
            return (IpsX_INSVIRMEM);
        tmp_offset = dst_offset;

        for (scanline = 0;  scanline < scanline_count; scanline++)
            {
            _BufferCombineBitonal(
                bit_count,                        /* Bit count          */
                src1_offset,                      /* src1 bit offset     */
                src1_udp->UdpA_Base,              /* buffer address */
                src2_offset,                      /* bit offset     */
                src2_udp->UdpA_Base,              /* buffer address */
                tmp_offset,                       /* bit offset     */
                tmp_dst_udp.UdpA_Base,            /* buffer adr     */
                operator);
            src1_offset += src1_udp->UdpL_ScnStride;
            src2_offset += src2_udp->UdpL_ScnStride;
            tmp_offset += tmp_dst_udp.UdpL_ScnStride;
            }
        status = _IpsCopy (&tmp_dst_udp, dst_udp, IpsM_RetainSrcDim);
        (*IpsA_MemoryTable[IpsK_FreeDataPlane]) (tmp_dst_udp.UdpA_Base);
        if (status != IpsX_SUCCESS)
            return (status);
        }
    else
        {
        /*
        ** On non-VMS platforms
        */
        for (scanline = 0;  scanline < scanline_count; scanline++)
            {
            _BufferCombineBitonal(
                bit_count,                        /* Bit count          */
                src1_offset,                      /* src1 bit offset     */
                src1_udp->UdpA_Base,              /* buffer address */
                src2_offset,                      /* bit offset     */
                src2_udp->UdpA_Base,              /* buffer address */
                dst_offset,                       /* bit offset     */
                dst_udp->UdpA_Base,               /* buffer adr     */
                operator);

            src1_offset += src1_udp->UdpL_ScnStride;
            src2_offset += src2_udp->UdpL_ScnStride;
            dst_offset += dst_udp->UdpL_ScnStride;
            }
        }

#endif

return (IpsX_SUCCESS);
}/* end of _IpsLogicalCombine */

/************************************************************************
**
**  _BufferCombineBitonal
**
**  FUNCTIONAL DESCRIPTION:
**
**  Performs a logical point combination on two bitonal input images.
**
**  FORMAL PARAMETERS:
**
    long		size;		* number of bits to combine	     *
    long		src1_addr;	* base address of source buf         *
    long		src1_pos;	* starting offset in source buf      *
    long		src2_addr;	* base address of source buf         *
    long		src2_pos;	* starting offset in source buf      *
    long		dst_addr;	* base address of destination buf    *
    long		dst_pos;	* starting offset in destination buf *
    long		rule;		* combination rule                   *
**
**  IMPLICIT INPUTS:  None
**  IMPLICIT OUTPUTS: None
**  FUNCTION VALUE:   None
**  SIGNAL CODES:     None
**  SIDE EFFECTS:     None
**
************************************************************************/

long _BufferCombineBitonal
    (size,src1_pos,src1_addr,src2_pos,src2_addr,dst_pos,dst_addr, rule)
long		size;		/* size of bits to be combined         */
long		src1_pos;	/* starting offset in source1 buf      */
unsigned char 	*src1_addr;	/* base address of source1 buf         */
long		src2_pos;	/* starting offset in source2 buf      */
unsigned char	*src2_addr;	/* base address of source2 buf         */
long		dst_pos;	/* starting offset in destination buf  */
unsigned char	*dst_addr;	/* base address of destination buf     */
long		rule;		/* combination rule                    */
{
unsigned char	value;
long		src1_offset, src2_offset, dst_offset;
long		bits;
unsigned long	i,j;
/* 
** This is for combine bits bitonal where we work on sizes of longs.
** If we are to work on bytes, then cast out_value as unsigned char.  
** Also have result_dst become a byte pointer.
** Note: this code IS sensitive to big endian and little endian differences
** as well as byte ordereing within a chunk if it exceeds 8 bits
*/
unsigned int   *result_dst;
unsigned long   num_of_chunks, out_value;
unsigned long	chunks = 32;
unsigned char	chunk_shift = 5;

/*
* obtain pointers to the source and destination buffers
*/

dst_offset = dst_pos;
src1_offset = src1_pos;
src2_offset = src2_pos;

/* 
** If less than chunks make one call and return
*/
if (size < chunks)
    {
    _DoBits(size, src1_offset, src1_addr, src2_offset, src2_addr,
	    dst_offset, dst_addr, rule);
    return;
    }

/*
** Do enough bits to line up destination to boundary indicated by chunks
*/

bits = chunks - (dst_offset % chunks);

if (bits != chunks)
    {
    _DoBits(bits, src1_offset, src1_addr, src2_offset, src2_addr,
	    dst_offset, dst_addr, rule);
    size -= bits;
    dst_offset += bits;
    src1_offset += bits;
    src2_offset += bits;
    }
    
num_of_chunks = size >> chunk_shift;

if (num_of_chunks != 0)
    {
    /*
    ** Do chunks (int) til leftovers
    */
    result_dst = (unsigned int *)dst_addr;
    result_dst += (dst_offset>>chunk_shift);

    result_dst += (num_of_chunks - 1);   /* goto end of ints and work backwords*/
    src1_offset += (num_of_chunks << chunk_shift) - 1;
    src2_offset += (num_of_chunks << chunk_shift) - 1;

    switch (rule)
        {
        case IpsK_Src1AndSrc2:
        for (j = 0; j < num_of_chunks; j++)
	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = GET_BIT_VALUE_(src1_addr, src1_offset) &
		    GET_BIT_VALUE_(src2_addr,src2_offset);
	        out_value = (out_value<<1) | value;
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;
    
        case IpsK_Src1AndNotSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = GET_BIT_VALUE_(src1_addr, src1_offset) & 
		    ~(GET_BIT_VALUE_(src2_addr,src2_offset));
	        out_value = (out_value<<1) | value;
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;
    
        case IpsK_NotSrc1AndSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = ~(GET_BIT_VALUE_(src1_addr, src1_offset)) & 
		    GET_BIT_VALUE_(src2_addr,src2_offset);
	        out_value = (out_value<<1) | value;
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;
    
        case IpsK_Src1XorSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
 	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = GET_BIT_VALUE_(src1_addr, src1_offset) ^
		    GET_BIT_VALUE_(src2_addr,src2_offset);
	        out_value = (out_value<<1) | value;
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;
    
        case IpsK_Src1OrSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = GET_BIT_VALUE_(src1_addr, src1_offset) | 
		    GET_BIT_VALUE_(src2_addr,src2_offset);
	        out_value = (out_value<<1) | value;
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;
    
        case IpsK_NotSrc1AndNotSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
  	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = ~(GET_BIT_VALUE_(src1_addr, src1_offset)) & 
	 	    ~(GET_BIT_VALUE_(src2_addr,src2_offset));
	        out_value = (out_value<<1) | (value & 1);
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;
    
        case IpsK_NotSrc1XorSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = ~(GET_BIT_VALUE_(src1_addr, src1_offset)) ^ 
	    	    GET_BIT_VALUE_(src2_addr,src2_offset);
	        out_value = (out_value<<1) | (value & 1);
	        src1_offset--;
	        src2_offset--;
	        } 
	    *result_dst-- = out_value;
	    }
        break;
    
        case IpsK_Src1OrNotSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = GET_BIT_VALUE_(src1_addr, src1_offset) |
	    	    ~(GET_BIT_VALUE_(src2_addr,src2_offset));
	        out_value = (out_value<<1) | (value & 1);
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;
    
        case IpsK_NotSrc1OrSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
   	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = ~(GET_BIT_VALUE_(src1_addr, src1_offset)) |
		    GET_BIT_VALUE_(src2_addr,src2_offset);
	        out_value = (out_value<<1) | (value & 1);
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;
    
        case IpsK_NotSrc1OrNotSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = ~(GET_BIT_VALUE_(src1_addr, src1_offset)) |
	    	    ~(GET_BIT_VALUE_(src2_addr,src2_offset));
	        out_value = (out_value<<1) | (value & 1);
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;
    
        case IpsK_SetToSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = GET_BIT_VALUE_(src2_addr,src2_offset);
	        out_value = (out_value<<1) | value;
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;

        case IpsK_SetToNotSrc2:
        for (j = 0 ; j < num_of_chunks; j++)
	    {
	    out_value = 0;
	    for (i = 0; i < chunks; i++)
	        {
	        value = ~(GET_BIT_VALUE_(src2_addr,src2_offset));
	        out_value = (out_value<<1) | (value & 1);
	        src1_offset--;
	        src2_offset--;
	        }
	    *result_dst-- = out_value;
	    }
        break;

        default:
        break;
        }
    }


size -= (num_of_chunks<<chunk_shift);

if (size != 0)
    {
    /* reset offsets to end of line */
    src1_offset += (num_of_chunks << chunk_shift);
    src2_offset += (num_of_chunks << chunk_shift);
    dst_offset += (num_of_chunks<<chunk_shift);
    /* Increment the offsets for source and destination if we have
    ** done any chunks. The sources were decremented one too many.
    */
    if (num_of_chunks != 0)
        {
        src1_offset += 1;
        src2_offset += 1;
        }

    _DoBits(size, src1_offset, src1_addr, src2_offset, src2_addr,
	    dst_offset, dst_addr, rule);
    }
}

void _DoBits(bits ,src1_offset, src1, src2_offset, src2, dst_offset, dst, rule)
long		bits;		/* size of bits to be combined         */
long		src1_offset;	/* starting offset in source1 buf      */
unsigned char	*src1;		/* base address of source1 buf         */
long		src2_offset;	/* starting offset in source2 buf      */
unsigned char   *src2;		/* base address of source2 buf         */
long		dst_offset;	/* starting offset in destination buf  */
unsigned char   *dst;		/* base address of destination buf     */
long		rule;		/* combination rule                    */
{
unsigned char value;

    /*
    ** apply the rule
    */
     switch (rule)
        {
	case IpsK_Src1AndSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{
		value = GET_BIT_VALUE_(src1, src1_offset) & 
			GET_BIT_VALUE_(src2,src2_offset);
		PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
    
	case IpsK_Src1AndNotSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{
	        value = GET_BIT_VALUE_(src1, src1_offset) & 
			~(GET_BIT_VALUE_(src2,src2_offset));
	        PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
    
	case IpsK_NotSrc1AndSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{
	        value = ~(GET_BIT_VALUE_(src1, src1_offset)) & 
	    		GET_BIT_VALUE_(src2,src2_offset);
	        PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
    
	case IpsK_Src1XorSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
	        {
	        value = GET_BIT_VALUE_(src1, src1_offset) ^
			GET_BIT_VALUE_(src2,src2_offset);
	        PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
    
	case IpsK_Src1OrSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{
	        value = GET_BIT_VALUE_(src1, src1_offset) | 
	    		GET_BIT_VALUE_(src2,src2_offset);
	        PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
    
	case IpsK_NotSrc1AndNotSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{
	        value = ~(GET_BIT_VALUE_(src1, src1_offset)) & 
			~(GET_BIT_VALUE_(src2,src2_offset));
	        PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
    
	case IpsK_NotSrc1XorSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{
	        value = ~(GET_BIT_VALUE_(src1, src1_offset)) ^ 
	    		GET_BIT_VALUE_(src2,src2_offset);
	        PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
    
	case IpsK_Src1OrNotSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{
	        value = GET_BIT_VALUE_(src1, src1_offset) |
	    		~(GET_BIT_VALUE_(src2,src2_offset));
	        PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
    
	case IpsK_NotSrc1OrSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{
	        value = ~(GET_BIT_VALUE_(src1, src1_offset)) |
	    		GET_BIT_VALUE_(src2,src2_offset);
	        PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
    
	case IpsK_NotSrc1OrNotSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{	
	        value = ~(GET_BIT_VALUE_(src1, src1_offset)) |
	    		~(GET_BIT_VALUE_(src2,src2_offset));
	        PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
    
	case IpsK_SetToSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{
	        value = GET_BIT_VALUE_(src2,src2_offset);
	        PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;

	case IpsK_SetToNotSrc2:
	    for (;bits > 0; src1_offset++, dst_offset++, src2_offset++, bits--)
		{	
		value = ~(GET_BIT_VALUE_(src2,src2_offset));
		PUT_BIT_VALUE_(dst,dst_offset,value);
		}
	break;
	default:
	break;
        }/* end switch on rule */

}/* end _DoBits */
