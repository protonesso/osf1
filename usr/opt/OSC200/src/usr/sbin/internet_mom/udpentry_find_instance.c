/*
 * *****************************************************************
 * *                                                               *
 * *    Copyright (c) Digital Equipment Corporation, 1991, 1994    *
 * *                                                               *
 * *   All Rights Reserved.  Unpublished rights  reserved  under   *
 * *   the copyright laws of the United States.                    *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Digital   *
 * *   Equipment Corporation.  Possession, use,  duplication  or   *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Digital Equipment  *
 * *   Corporation.                                                *
 * *                                                               *
 * *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
 * *   by the U.S. Government is subject to restrictions  as  set  *
 * *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
 * *   or  in  FAR 52.227-19, as applicable.                       *
 * *                                                               *
 * *****************************************************************
 */
/*
 * HISTORY
 */
#ifndef lint
static char *rcsid = "@(#)$RCSfile: udpentry_find_instance.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1993/04/26 21:46:55 $";
#endif
/*
**++
**  FACILITY:  ZKO3-3
**
**  Copyright (c) 1993  Digital Equipment Corporation
**
**  MODULE DESCRIPTION:
**
**	udpEntry_FIND_INSTANCE.C
**
**      This module is part of the Managed Object Module (MOM)
**	for rfc1213.
**
**	This module provides the routines that may need modification if the
**	udpEntry class obtains its data outside of this process.
**
**  AUTHORS:
**
**      Geetha M. Brown
**
**      This code was initially created with the 
**	Ultrix MOM Generator - version X1.1.0
**
**  CREATION DATE:  01-Apr-1993
**
**  MODIFICATION HISTORY:
**
**
**--
*/

#include "moss.h"
#include "moss_inet.h"
#include "extern_nil.h"
#ifdef VMS
#include "descrip.h"
#include "str$routines.h"
#include "strdef.h"
#else
extern	comparison  *table_array[];
#endif /* VMS */
#include "common.h"
#include "extern_common.h"


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      udpEntry_add_new_instance
**
**	This routine adds an instance structure to the queue of instances
**	during create instance time.
**
**	NOTE: This routine is intended to be used by a MOM that maintains
**	      process data. This routine needs to be modified (or it can be
**	      eliminated entirely) if its data resides outside of this MOM.
**
**  FORMAL PARAMETERS:
**
**	p - pointer to previous instance.
**	q - pointer to instance to add.
**
**  RETURN VALUES:
**
**      MAN_C_SUCCESS
**
**  SIDE EFFECTS:
**
**      None
**
**--
*/
man_status udpEntry_add_new_instance( p, q )

udpEntry_DEF *p;
udpEntry_DEF *q;

{
    q->next = p->next;
    q->prev = p;
    p->next->prev = q;
    p->next = q;
return MAN_C_SUCCESS;
}

/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      udpEntry_locate_instance
**
**	This routine compares the instance against the queue of instances
**	found in new_udpEntry_header returning a pointer to that
**	instance if a match is found.
**
**	This routine is called at create time to verify that a duplicate
**	instance will not get created. Therefore, no wildcarding needs to
**	be performed since wildcarded creates are not allowed.
**
**	NOTE: This routine is intended to be used by a MOM that maintains
**	      process data. This routine needs to be modified (or it can be
**	      eliminated entirely) if data resides outside of this MOM.
**
**	This routine uses the object instance (if it exists) to match the
**	existing instance. This is used in place of the string sinc the
** 	does not contain the parent instance.
**
**  FORMAL PARAMETERS:
**
**	object_instance     - Pointer to object instance to compare.
**	instance_name       - Pointer to string containing instance to look for.
**	instance_length	    - Integer containing length of string to compare.
**	return_instance_ptr - Address of pointer to return match if any.
**
**  RETURN VALUES:
**
**      MAN_C_TRUE  - if match found
**	MAN_C_FALSE - if no match found
**
**  SIDE EFFECTS:
**
**      None
**
**--
*/
man_status udpEntry_locate_instance(
					   object_instance,
					   instance_name,
					   instance_length,
			   		   return_instance_ptr )

avl			*object_instance;
char			*instance_name;
int		 	instance_length;
udpEntry_DEF	**return_instance_ptr;

{
    man_status status;
    udpEntry_DEF *instance;

    instance = new_udpEntry_header->next;

    while (instance != new_udpEntry_header)
    {
      status = MAN_C_FALSE;
      if ((instance->object_instance != NULL) && (object_instance != NULL))

#ifdef VMS
          status = moss_match_instance_name( object_instance, 
					     instance->object_instance, 
					     0, 
					     NULL );
#else
          status = moss_match_instance_name( object_instance, 
					     instance->object_instance, 
					     0, 
					     table_array );
#endif

      else if ((instance_length == instance->instance_name_length) &&
	   (strncmp( instance->instance_name, instance_name, instance_length ) == 0))
	       status = MAN_C_TRUE;

      if (status == MAN_C_TRUE)
	  {
	  if (return_instance_ptr != NULL)
	     *return_instance_ptr = instance;
          return status;
    	  }

      if (status == MAN_C_FALSE)
          instance = instance->next;
      else
	 return status;
   }

    return MAN_C_FALSE;
}

/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      udpEntry_build_instance
**
**  FORMAL PARAMETERS:
**
**	object_instance - Pointer to object instance to match.
**	return_instance - Address of pointer to candidate instance to build.
**	context  	- Pointer to context structure block.
**
**  RETURN VALUES:
**
**      MAN_C_TRUE  - if match found
**	MAN_C_FALSE - if no match found
**
**  SIDE EFFECTS:
**
**      None
**
**--
*/
static man_status udpEntry_build_instance(
		      				 object_instance,
		      				 return_instance,
		      				 context )

avl		    *object_instance;
avl		    **return_instance;
GET_CONTEXT_STRUCT  *context;

{
    avl			    *candidate_instance = NULL;
    man_status		    moss_status;
    object_id		    *cand_oid;
    object_id               *copy_oid;
    unsigned int	    cand_modifier;
    unsigned int            copy_modifier;
    unsigned int	    cand_tag;
    unsigned int            copy_tag;
    octet_string	    *cand_octet;
    octet_string            *temp_octet;
    octet_string            *copy_octet;
    int			    last_one ;

    /* 
     * Build a full instance specification from the information in 
     * the context block and the requested instance.
     */

    moss_status = moss_avl_reset( object_instance );
    if ERROR_CONDITION( moss_status )
        return moss_status;

    moss_status = moss_avl_init( &candidate_instance );
    if ERROR_CONDITION( moss_status )
        return moss_status;

    moss_status = moss_avl_point( object_instance, NULL, NULL, &copy_tag, NULL, &last_one);
    if ((moss_status != MAN_C_SUCCESS) || (copy_tag != ASN1_C_SEQUENCE)) 
	{
	/* 
	 * AVL in request is not an instance specification 
	 */
	moss_avl_free( &candidate_instance, TRUE );
	return MAN_C_FALSE;	    
	}

	moss_status = moss_avl_start_construct (candidate_instance, NULL, 0, ASN1_C_SEQUENCE, NULL);
        if ERROR_CONDITION( moss_status )
            {
            moss_avl_free( &candidate_instance, TRUE );
            return moss_status;
            }

	/* 
	 * Copy elements until we hit the end...last one gets 
	 * copy of instance information from context block 
	 */
	do {	
           char   *ch_ptr;
	    moss_status = moss_avl_point( object_instance, &copy_oid, &copy_modifier, &copy_tag, &copy_octet, &last_one);
            if ERROR_CONDITION( moss_status )
                {
                moss_avl_free( &candidate_instance, TRUE );
                return moss_status;
                }

	    if (copy_tag == ASN1_C_EOC) 
		{		/* EOC is last element */
		moss_avl_backup( candidate_instance );	/* back up and remove last element copied */
		moss_avl_backup( candidate_instance );	/* back up and remove last element copied */
		moss_avl_remove( candidate_instance );
		moss_avl_remove( candidate_instance );
		cand_octet = (octet_string *)malloc(sizeof(*temp_octet));
                if (cand_octet == NULL)
                    {
                    moss_avl_free( &candidate_instance, TRUE );
                    return MAN_C_PROCESSING_FAILURE;
                    }

		memcpy(cand_octet, temp_octet, sizeof(*temp_octet));
		if (cand_tag == ASN1_C_NULL) 
		    { /* was it a null instance ? */

		    if (context->udpEntry_PTR->instance_name_length != 0) 
			{   /* candidate instance isn't null */
			moss_avl_free( &candidate_instance, TRUE );
			return MAN_C_FALSE;
		    	}
		    cand_octet->length = 0;		/* fill in element with null instance */
		    cand_octet->data_type = ASN1_C_NULL;
		    cand_octet->string = NULL;
		    }
		else 
		    {	
		    /* 
		     * Fill in candidate instance octet with info from context block 
		     */
		    ch_ptr = (char *)malloc(sizeof(int));
		    if (ch_ptr == NULL) {
                        return(MAN_C_INSUFFICIENT_RESOURCES);
                    }
                    bcopy((char *)&context->udpEntry_PTR->udpLocalAddress,
                          ch_ptr, sizeof(int));
                    cand_octet->string = (char *)ch_ptr;
                    cand_octet->length = sizeof (int) ;
                    cand_octet->data_type = INET_C_SMI_IP_ADDRESS;
                    cand_tag = INET_C_SMI_IP_ADDRESS;
                moss_status = moss_avl_add( candidate_instance,
#ifdef DNA_CMIP_OID
                            &udpEntry_ATTR_udpLocalAddress_DNA,
#endif /* DNA_CMIP_OID */
#ifdef SNMP_OID
                            &udpEntry_ATTR_udpLocalAddress_SNP,
#endif /* SNMP_OID */
/** Multiple identifier OIDs found. Verify the correct OID **/
                            cand_modifier,
                            cand_tag,
                            cand_octet);

                    cand_octet->length = sizeof (int) ;
                    cand_octet->data_type = ASN1_C_INTEGER;
                    cand_octet->string = (char *)&context->udpEntry_PTR->udpLocalPort;
                    cand_tag = ASN1_C_INTEGER;
                    }
		moss_status = moss_avl_add( candidate_instance,
#ifdef DNA_CMIP_OID 
                               &udpEntry_ATTR_udpLocalPort_DNA,
#endif /* DNA_CMIP_OID */
#ifdef SNMP_OID
                               &udpEntry_ATTR_udpLocalPort_SNP,
#endif /* SNMP_OID */
/** Multiple identifier OIDs found. Verify the correct OID **/
			    cand_modifier,
			    cand_tag,
			    cand_octet);

                free( cand_octet );

                if ERROR_CONDITION( moss_status )
                    {
                    moss_avl_free( &candidate_instance, TRUE );
                    return moss_status;
                    }
	        }
	    else {
		temp_octet = copy_octet;    /* save avl info for backup step */
		cand_modifier = copy_modifier;
		cand_tag = copy_tag;
		moss_status = moss_avl_add( candidate_instance, copy_oid, copy_modifier, copy_tag, copy_octet);

                if ERROR_CONDITION( moss_status )
                    {
                    moss_avl_free( &candidate_instance, TRUE );
                    return moss_status;
                    }
	    }
	}
	while (copy_tag != ASN1_C_EOC);
	moss_status = moss_avl_end_construct (candidate_instance);	/* close candidate instance avl and compare to one requested */

        if ERROR_CONDITION( moss_status )
            {
            moss_avl_free( &candidate_instance, TRUE );
            return moss_status;
            }

    *return_instance = candidate_instance;

    return MAN_C_SUCCESS;            
}

/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      udpEntry_get_next_match
**
**	This routine performs the steps needed to search through
**	the context block looking for a match between the requested
**	instance and candidate instances in the block.
**
**	NOTE: This routine is intended to be used by a MOM that maintains
**	      process data. This routine needs to be modified (or it can be
**	      eliminated entirely) if data resides outside of this MOM.
**
**  FORMAL PARAMETERS:
**
**	context  - pointer to context structure block.
**
**  RETURN VALUES:
**
**      MAN_C_TRUE  - if match found
**	MAN_C_FALSE - if no match found
**
**  SIDE EFFECTS:
**
**      None
**
**--
*/
man_status udpEntry_get_next_match( object_instance,
					   iso_scope,
					   context )

avl		    *object_instance;
scope		    iso_scope;
GET_CONTEXT_STRUCT  *context;

{
    avl		*candidate_instance = (avl *)NULL;
    avl		*save_candidate_instance = (avl *) NULL;
    man_status	status = MAN_C_FALSE;

    moss_avl_reset( object_instance );    /* reset requested instance */
    context->udpEntry_PTR = context->udpEntry_PTR->next;

    /* Loop through instances to see if there is a match */

    while ((context->udpEntry_PTR != new_udpEntry_header) && (status == MAN_C_FALSE))
    {
        candidate_instance = context->udpEntry_PTR->object_instance;

	/* 
	 * Check to make sure we have a valid candidate instance. If not, build one from
	 * the instance_name and length.
	 */

	if (candidate_instance == NULL)
	    {
	    status = udpEntry_build_instance( object_instance, 
					    	     &candidate_instance, 
					    	     context );
	    if ERROR_CONDITION( status )
		return status;

/**
    developer's note for moms which do not support the create directive:

    the developer may use the following code to save the built instance in the
    structure to avoid rebuilding the instance on each request.  this is not
    recommended if the developer is using a single structure and loading it
    on each call.

            moss_avl_init (&context->udpEntry_PTR->object_instance);
            moss_avl_reset (candidate_instance);
            moss_avl_copy (context->udpEntry_PTR->object_instance,
                            candidate_instance,
                            TRUE,
                            NULL,
                            NULL,
                            NULL );
            moss_avl_reset (candidate_instance);
 **/
	    save_candidate_instance = candidate_instance;
	    }	    

#ifdef VMS
	status = moss_match_instance_name( object_instance, 
					   candidate_instance, 
					   iso_scope, 
					   NULL );
#else
	status = moss_match_instance_name( object_instance, 
					   candidate_instance, 
					   iso_scope, 
					   table_array );
#endif

	if (status == MAN_C_FALSE) {
	    context->udpEntry_PTR = context->udpEntry_PTR->next;

	if (save_candidate_instance != NULL)
	    moss_avl_free( &save_candidate_instance, TRUE );

	moss_avl_reset( object_instance );
	}
    } 

    context->first_time = FALSE;

    if (save_candidate_instance != NULL)
	moss_avl_free( &save_candidate_instance, TRUE );

    if (status != MAN_C_TRUE)
	return MAN_C_FALSE;

    return MAN_C_TRUE;

}    
