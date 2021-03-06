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
/* $XConsortium: FSproto.h,v 1.8 92/11/18 21:31:32 gildea Exp $ */
/*
 * Copyright 1990, 1991 Network Computing Devices;
 * Portions Copyright 1987 by Digital Equipment Corporation and the
 * Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the names of Network Computing Devices, Digital or
 * M.I.T. not be used in advertising or publicity pertaining to distribution
 * of the software without specific, written prior permission.
 *
 * NETWORK COMPUTING DEVICES, DIGITAL AND M.I.T. DISCLAIM ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL NETWORK COMPUTING DEVICES,
 * DIGITAL OR M.I.T. BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
 * THIS SOFTWARE.
 */

#ifndef _FS_PROTO_H_
#define _FS_PROTO_H_

#include	"FS.h"
#include	<X11/Xmd.h>

#define sz_fsPropOffset 20
#define sz_fsPropInfo 8
#define sz_fsResolution 6

#define sz_fsChar2b 2
#define sz_fsChar2b_version1 2
#define sz_fsOffset32 8
#define sz_fsRange		4

#define	sz_fsXCharInfo		12
#define	sz_fsXFontInfoHeader		40

#define	sz_fsConnClientPrefix	8
#define	sz_fsConnSetup		12
#define	sz_fsConnSetupExtra	8
#define	sz_fsConnSetupAccept	12

/* request sizes */
#define	sz_fsReq		4
#define	sz_fsListExtensionsReq	4
#define	sz_fsResourceReq	8

#define	sz_fsNoopReq			4
#define	sz_fsListExtensionReq		4
#define	sz_fsQueryExtensionReq		4
#define	sz_fsListCataloguesReq		12
#define	sz_fsSetCataloguesReq		4
#define	sz_fsGetCataloguesReq		4
#define	sz_fsSetEventMaskReq		8
#define	sz_fsGetEventMaskReq		4
#define	sz_fsCreateACReq		8
#define	sz_fsFreeACReq			8
#define	sz_fsSetAuthorizationReq	8
#define	sz_fsSetResolutionReq		4
#define	sz_fsGetResolutionReq		4
#define	sz_fsListFontsReq		12
#define	sz_fsListFontsWithXInfoReq	12
#define	sz_fsOpenBitmapFontReq		16
#define	sz_fsQueryXInfoReq		8
#define	sz_fsQueryXExtents8Req		12
#define	sz_fsQueryXExtents16Req		12
#define	sz_fsQueryXBitmaps8Req		16
#define	sz_fsQueryXBitmaps16Req		16
#define	sz_fsCloseReq			8

/* reply sizes */
#define	sz_fsReply			8
#define	sz_fsGenericReply		8

#define	sz_fsListExtensionsReply	8
#define	sz_fsQueryExtensionReply	20
#define	sz_fsListCataloguesReply	16
#define	sz_fsGetCataloguesReply		8
#define	sz_fsGetEventMaskReply		12
#define	sz_fsCreateACReply		12
#define	sz_fsGetResolutionReply		8
#define	sz_fsListFontsReply		16
#define	sz_fsListFontsWithXInfoReply	(12 + sz_fsXFontInfoHeader)
#define	sz_fsOpenBitmapFontReply	16
#define	sz_fsQueryXInfoReply		(8 + sz_fsXFontInfoHeader)
#define	sz_fsQueryXExtents8Reply	12
#define	sz_fsQueryXExtents16Reply	12
#define	sz_fsQueryXBitmaps8Reply	20
#define	sz_fsQueryXBitmaps16Reply	20

#define	sz_fsError		16
#define	sz_fsEvent		12
#define sz_fsKeepAliveEvent 	12

#define	fsTrue	1
#define	fsFalse	0

/* temp decls */
#define	Mask		CARD32
#define	Font		CARD32
#define	AccContext	CARD32

typedef CARD32	fsTimestamp;

#ifdef NOTDEF /* in fsmasks.h */
typedef CARD32	fsBitmapFormat;
typedef CARD32	fsBitmapFormatMask;
#endif
 
#define sz_fsBitmapFormat	4

typedef struct {
    INT16 	left B16,
                right B16;
    INT16 	width B16;
    INT16 	ascent B16,
                descent B16;
    CARD16 	attributes B16;
}           fsXCharInfo;

typedef struct {
    CARD8       high;
    CARD8       low;
}           fsChar2b;

typedef struct {
    CARD8       low;
    CARD8       high;
}           fsChar2b_version1;

typedef struct {
    CARD8	min_char_high;
    CARD8	min_char_low;
    CARD8	max_char_high;
    CARD8	max_char_low;
}           fsRange;

typedef struct	{
    CARD32	position B32;
    CARD32	length B32;
}	    fsOffset32;

typedef struct {
    fsOffset32	name;
    fsOffset32	value;
    CARD8 	type;
    BYTE        pad0;
    CARD16	pad1 B16;
}           fsPropOffset;

typedef struct {
    CARD32	num_offsets B32;
    CARD32	data_len B32;
    /* offsets */
    /* data */
}	    fsPropInfo;

typedef struct {
    CARD16	x_resolution B16;
    CARD16	y_resolution B16;
    CARD16	point_size B16;
}	    fsResolution;

  
typedef struct {
    CARD32	flags B32;
    CARD8	char_range_min_char_high;
    CARD8	char_range_min_char_low;
    CARD8	char_range_max_char_high;
    CARD8	char_range_max_char_low;

    CARD8	draw_direction;
    CARD8	pad;
    CARD8	default_char_high;
    CARD8	default_char_low;
    INT16	min_bounds_left B16;
    INT16	min_bounds_right B16;

    INT16	min_bounds_width B16;
    INT16	min_bounds_ascent B16;
    INT16	min_bounds_descent B16;
    CARD16	min_bounds_attributes B16;

    INT16	max_bounds_left B16;
    INT16	max_bounds_right B16;
    INT16	max_bounds_width B16;
    INT16	max_bounds_ascent B16;

    INT16	max_bounds_descent B16;
    CARD16	max_bounds_attributes B16;
    INT16	font_ascent B16;
    INT16	font_descent B16;
    /* propinfo */
}           fsXFontInfoHeader;


/* requests */

typedef struct {
    BYTE        byteOrder;
    CARD8       num_auths;
    CARD16 	major_version B16;
    CARD16 	minor_version B16;
    CARD16 	auth_len B16;
    /* auth data */
}           fsConnClientPrefix;

typedef struct {
    CARD16      status B16;
    CARD16 	major_version B16;
    CARD16 	minor_version B16;
    CARD8	num_alternates;
    CARD8	auth_index;
    CARD16	alternate_len B16;
    CARD16	auth_len B16;
    /* alternates */
    /* auth data */
}           fsConnSetup;

typedef struct {
    CARD32	length B32;
    CARD16      status B16;
    CARD16	pad B16;
    /* more auth data */
}           fsConnSetupExtra;

typedef struct {
    CARD32	length B32;
    CARD16	max_request_len B16;
    CARD16	vendor_len B16;
    CARD32	release_number B32;
    /* vendor string */
}	    fsConnSetupAccept;

typedef struct {
    CARD8       reqType;
    CARD8       data;
    CARD16 	length B16;
}           fsReq;

/*
 * The fsFakeReq structure is never used in the protocol; it is prepended
 * to incoming packets when setting up a connection so we can index
 * through InitialVector.  To avoid alignment problems, it is padded
 * to the size of a word on the largest machine this code runs on.
 * Hence no sz_fsFakeReq constant is necessary.
 */
typedef struct {
    CARD8       reqType;
    CARD8       data;
    CARD16 	length B16;
    CARD32	pad B32;	/* to fill out to multiple of 64 bits */
}           fsFakeReq;

typedef struct {
    CARD8       reqType;
    BYTE        pad;
    CARD16      length B16;
    Font        id B32;
}           fsResourceReq;

typedef fsReq	fsNoopReq;
typedef fsReq	fsListExtensionsReq;

typedef struct {
    CARD8       reqType;
    BYTE        nbytes;
    CARD16 	length B16;
    /* name */
}           fsQueryExtensionReq;

typedef struct {
    CARD8       reqType;
    CARD8       data;
    CARD16 	length B16;
    CARD32 	maxNames B32;
    CARD16 	nbytes B16;
    CARD16 	pad2 B16;
    /* pattern */
}	    fsListCataloguesReq;

typedef struct {
    CARD8       reqType;
    BYTE        num_catalogues;
    CARD16 	length B16;
    /* catalogues */
}           fsSetCataloguesReq;

typedef fsReq	fsGetCataloguesReq;

typedef struct {
    CARD8       reqType;
    CARD8       ext_opcode;
    CARD16 	length B16;
    Mask	event_mask;
}           fsSetEventMaskReq;

typedef struct {
    CARD8       reqType;
    CARD8       ext_opcode;
    CARD16 	length B16;
}           fsGetEventMaskReq;

typedef struct {
    CARD8       reqType;
    BYTE        num_auths;
    CARD16      length B16;
    AccContext  acid B32;
    /* auth protocols */
}           fsCreateACReq;

typedef fsResourceReq	fsFreeACReq;
typedef fsResourceReq	fsSetAuthorizationReq;

typedef struct {
    CARD8	reqType;
    BYTE	num_resolutions;
    CARD16	length B16;
    /* resolutions */
}	    fsSetResolutionReq;

typedef fsReq	fsGetResolutionReq;

typedef struct {
    CARD8       reqType;
    BYTE        pad;
    CARD16 	length B16;
    CARD32 	maxNames B32;
    CARD16 	nbytes B16;
    CARD16 	pad2 B16;
    /* pattern */
}           fsListFontsReq;

typedef fsListFontsReq fsListFontsWithXInfoReq;

typedef struct {
    CARD8       reqType;
    BYTE        pad;
    CARD16 	length B16;
    Font 	fid B32;
    fsBitmapFormatMask format_mask B32;
    fsBitmapFormat format_hint B32;
    /* pattern */
}           fsOpenBitmapFontReq;

typedef fsResourceReq fsQueryXInfoReq;

typedef struct {
    CARD8       reqType;
    BOOL        range;
    CARD16 	length B16;
    Font 	fid B32;
    CARD32	num_ranges B32;
    /* list of chars */
}           fsQueryXExtents8Req;

typedef fsQueryXExtents8Req	fsQueryXExtents16Req;

typedef struct {
    CARD8       reqType;
    BOOL	range;
    CARD16 	length B16;
    Font 	fid B32;
    fsBitmapFormat format B32;
    CARD32	num_ranges B32;
    /* list of chars */
}           fsQueryXBitmaps8Req;

typedef fsQueryXBitmaps8Req	fsQueryXBitmaps16Req;

typedef fsResourceReq fsCloseReq;


/* replies */
typedef struct {
    BYTE        type;
    BYTE        data1;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
}           fsGenericReply;

typedef struct {
    BYTE        type;
    CARD8       nExtensions;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    /* extension names */
}           fsListExtensionsReply;

typedef struct {
    BYTE        type;
    CARD8       present;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    CARD16	major_version B16;
    CARD16	minor_version B16;
    CARD8       major_opcode;
    CARD8       first_event;
    CARD8       num_events;
    CARD8       first_error;
    CARD8       num_errors;
    CARD8	pad1;
    CARD16	pad2 B16;
}           fsQueryExtensionReply;

typedef struct {
    BYTE        type;
    BYTE        pad;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    CARD32	num_replies B32;
    CARD32	num_catalogues B32;
    /* catalog names */
}	    fsListCataloguesReply;

typedef struct {
    BYTE        type;
    CARD8       num_catalogues;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    /* catalogue names */
}           fsGetCataloguesReply;

typedef struct {
    BYTE        type;
    BYTE        pad1;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    CARD32 	event_mask B32;
}	    fsGetEventMaskReply;

typedef struct {
    BYTE	type;
    CARD8	auth_index;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	status B16;
    CARD16	pad B16;
    /* auth data */
}	    fsCreateACReply;

typedef struct {
    CARD32	length B32;
    CARD16	status B16;
    CARD16	pad B16;
    /* auth data */
}	    fsCreateACExtraReply;

typedef struct {
    BYTE	type;
    CARD8	num_resolutions;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    /* resolutions */
}	    fsGetResolutionReply;

typedef struct {
    BYTE        type;
    BYTE        pad1;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    CARD32	following B32;
    CARD32 	nFonts B32;
    /* font names */
}           fsListFontsReply;

/*
 * this one is messy.  the reply itself is variable length (unknown
 * number of replies) and the contents of each is variable (unknown
 * number of properties)
 *
 */

typedef struct {
    BYTE        type;
    CARD8       nameLength;	/* 0 is end-of-reply */
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    CARD32 	nReplies B32;
    CARD32	font_header_flags B32;
    CARD8	font_header_char_range_min_char_high;
    CARD8	font_header_char_range_min_char_low;
    CARD8	font_header_char_range_max_char_high;
    CARD8	font_header_char_range_max_char_low;
    CARD8	font_header_draw_direction;
    CARD8	font_header_pad;
    CARD8	font_header_default_char_high;
    CARD8	font_header_default_char_low;
    INT16	font_header_min_bounds_left B16;
    INT16	font_header_min_bounds_right B16;
    INT16	font_header_min_bounds_width B16;
    INT16	font_header_min_bounds_ascent B16;
    INT16	font_header_min_bounds_descent B16;
    CARD16	font_header_min_bounds_attributes B16;
    INT16	font_header_max_bounds_left B16;
    INT16	font_header_max_bounds_right B16;
    INT16	font_header_max_bounds_width B16;
    INT16	font_header_max_bounds_ascent B16;
    INT16	font_header_max_bounds_descent B16;
    CARD16	font_header_max_bounds_attributes B16;
    INT16	font_header_font_ascent B16;
    INT16	font_header_font_descent B16;
    /* propinfo */
    /* name */
}           fsListFontsWithXInfoReply;
    
typedef struct {
    BYTE        type;
    CARD8       otherid_valid;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    CARD32	otherid B32;
    BYTE	cachable;
    BYTE	pad1;
    CARD16	pad2 B16;
}           fsOpenBitmapFontReply;

typedef struct {
    BYTE        type;
    CARD8       pad0;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    CARD32	font_header_flags B32;
    CARD8	font_header_char_range_min_char_high;
    CARD8	font_header_char_range_min_char_low;
    CARD8	font_header_char_range_max_char_high;
    CARD8	font_header_char_range_max_char_low;
    CARD8	font_header_draw_direction;
    CARD8	font_header_pad;
    CARD8	font_header_default_char_high;
    CARD8	font_header_default_char_low;
    INT16	font_header_min_bounds_left B16;
    INT16	font_header_min_bounds_right B16;
    INT16	font_header_min_bounds_width B16;
    INT16	font_header_min_bounds_ascent B16;
    INT16	font_header_min_bounds_descent B16;
    CARD16	font_header_min_bounds_attributes B16;
    INT16	font_header_max_bounds_left B16;
    INT16	font_header_max_bounds_right B16;
    INT16	font_header_max_bounds_width B16;
    INT16	font_header_max_bounds_ascent B16;
    INT16	font_header_max_bounds_descent B16;
    CARD16	font_header_max_bounds_attributes B16;
    INT16	font_header_font_ascent B16;
    INT16	font_header_font_descent B16;
    /* propinfo */
}           fsQueryXInfoReply;

typedef struct {
    BYTE        type;
    CARD8       pad0;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    CARD32      num_extents B32;
    /* extents */
}           fsQueryXExtents8Reply;

typedef fsQueryXExtents8Reply	fsQueryXExtents16Reply;

typedef struct {
    BYTE        type;
    CARD8       pad0;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    CARD32	replies_hint B32;
    CARD32 	num_chars B32;
    CARD32	nbytes B32;
    /* offsets */
    /* glyphs */
}           fsQueryXBitmaps8Reply;

typedef fsQueryXBitmaps8Reply	fsQueryXBitmaps16Reply;

typedef union {
    fsGenericReply generic;
    fsListExtensionsReply extensions;
    fsGetResolutionReply getres;
}           fsReply;

/* errors */
typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
}	    fsError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
}	    fsRequestError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
    fsBitmapFormat	format B32;
}	    fsFormatError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
    Font	fontid;
}	    fsFontError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
    fsRange	range;
}	    fsRangeError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
    Mask	event_mask;
}	    fsEventMaskError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
    AccContext	acid;
}	    fsAccessContextError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
    Font	fontid;
}	    fsIDChoiceError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
}	    fsNameError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    fsResolution resolution;
}	    fsResolutionError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
}	    fsAllocError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
    CARD32	bad_length B32;
}	    fsLengthError;

typedef struct {
    BYTE        type;
    BYTE        request;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    CARD8	major_opcode;
    CARD8	minor_opcode;
    CARD16	pad B16;
}	    fsImplementationError;

/* events */
typedef struct {
    BYTE        type;
    BYTE        event_code;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
}	    fsKeepAliveEvent;

typedef struct {
    BYTE        type;
    BYTE        event_code;
    CARD16 	sequenceNumber B16;
    CARD32 	length B32;
    fsTimestamp	timestamp;
    BOOL	added;
    BOOL	deleted;
    CARD16	pad B16;
}	    fsCatalogueChangeNotifyEvent;

typedef fsCatalogueChangeNotifyEvent	fsFontChangeNotifyEvent;

typedef fsCatalogueChangeNotifyEvent	fsEvent;

/* reply codes */
#define	FS_Reply		0	/* normal reply */
#define	FS_Error		1	/* error */
#define	FS_Event		2

/* request codes */
#define		FS_Noop			0
#define		FS_ListExtensions	1
#define		FS_QueryExtension	2
#define		FS_ListCatalogues	3
#define		FS_SetCatalogues	4
#define		FS_GetCatalogues	5
#define		FS_SetEventMask		6
#define		FS_GetEventMask		7
#define		FS_CreateAC		8
#define		FS_FreeAC		9
#define		FS_SetAuthorization	10
#define		FS_SetResolution	11
#define		FS_GetResolution	12
#define		FS_ListFonts		13
#define		FS_ListFontsWithXInfo	14
#define		FS_OpenBitmapFont	15
#define		FS_QueryXInfo		16
#define		FS_QueryXExtents8	17
#define		FS_QueryXExtents16	18
#define		FS_QueryXBitmaps8	19
#define		FS_QueryXBitmaps16	20
#define		FS_CloseFont		21

/* restore decls */
#undef	Mask
#undef	Font
#undef  AccContext

#endif				/* _FS_PROTO_H_ */
