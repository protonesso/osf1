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
static char     *sccsid = "@(#)$RCSfile: key_prot.c,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1993/06/07 23:21:37 $";
#endif
/*
 */


/* 
 * Copyright (c) 1988 by Sun Microsystems, Inc.
 * 1.4 88/02/08 
 */

/* name space pollution clean up */
#ifdef _NAME_SPACE_WEAK_STRONG
#include "pollution.h"
#if !defined(_THREAD_SAFE)
#pragma weak xdr_cryptkeyarg = __xdr_cryptkeyarg
#pragma weak xdr_cryptkeyres = __xdr_cryptkeyres
#pragma weak xdr_getcredres = __xdr_getcredres
#pragma weak xdr_keybuf = __xdr_keybuf
#pragma weak xdr_keystatus = __xdr_keystatus
#pragma weak xdr_netnamestr = __xdr_netnamestr
#pragma weak xdr_unixcred = __xdr_unixcred
#endif
#endif
#ifdef KERNEL
#include "../rpc/rpc.h"
#include "../rpc/key_prot.h"
#else
#include <rpc/rpc.h>
#include <rpc/key_prot.h>
#endif


/* 
 * Compiled from key_prot.x using rpcgen.
 * DO NOT EDIT THIS FILE!
 * This is NOT source code!
 */


bool_t
xdr_keystatus(xdrs, objp)
	XDR *xdrs;
	keystatus *objp;
{
	if (!xdr_enum(xdrs, (enum_t *)objp)) {
		return (FALSE);
	}
	return (TRUE);
}


#ifndef KERNEL


bool_t
xdr_keybuf(xdrs, objp)
	XDR *xdrs;
	keybuf objp;
{
	if (!xdr_opaque(xdrs, objp, HEXKEYBYTES)) {
		return (FALSE);
	}
	return (TRUE);
}


#endif


bool_t
xdr_netnamestr(xdrs, objp)
	XDR *xdrs;
	netnamestr *objp;
{
	if (!xdr_string(xdrs, objp, MAXNETNAMELEN)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_cryptkeyarg(xdrs, objp)
	XDR *xdrs;
	cryptkeyarg *objp;
{
	if (!xdr_netnamestr(xdrs, &objp->remotename)) {
		return (FALSE);
	}
	if (!xdr_des_block(xdrs, &objp->deskey)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_cryptkeyres(xdrs, objp)
	XDR *xdrs;
	cryptkeyres *objp;
{
	if (!xdr_keystatus(xdrs, &objp->status)) {
		return (FALSE);
	}
	switch (objp->status) {
	case KEY_SUCCESS:
		if (!xdr_des_block(xdrs, &objp->cryptkeyres_u.deskey)) {
			return (FALSE);
		}
		break;
	}
	return (TRUE);
}




bool_t
xdr_unixcred(xdrs, objp)
	XDR *xdrs;
	unixcred *objp;
{
	if (!xdr_int(xdrs, (int *)&objp->uid)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, (int *)&objp->gid)) {
		return (FALSE);
	}
	if (!xdr_array(xdrs, (char **)&objp->gids.gids_val, (u_int *)&objp->gids.gids_len, MAXGIDS, sizeof(int), xdr_int)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_getcredres(xdrs, objp)
	XDR *xdrs;
	getcredres *objp;
{
	if (!xdr_keystatus(xdrs, &objp->status)) {
		return (FALSE);
	}
	switch (objp->status) {
	case KEY_SUCCESS:
		if (!xdr_unixcred(xdrs, &objp->getcredres_u.cred)) {
			return (FALSE);
		}
		break;
	}
	return (TRUE);
}


