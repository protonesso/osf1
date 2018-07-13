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
static char *sccsid = "@(#)$RCSfile: sm_inter.c,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 05:00:41 $";
#endif
/*
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 * @(#) from SUN 1.5
 */

#include <rpc/rpc.h>
#include <rpcsvc/sm_inter.h>

bool_t
xdr_sm_name(xdrs, objp)
	XDR *xdrs;
	sm_name *objp;
{
	if (!xdr_string(xdrs, &objp->mon_name, SM_MAXSTRLEN)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_my_id(xdrs, objp)
	XDR *xdrs;
	my_id *objp;
{
	if (!xdr_string(xdrs, &objp->my_name, SM_MAXSTRLEN)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->my_prog)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->my_vers)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->my_proc)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_mon_id(xdrs, objp)
	XDR *xdrs;
	mon_id *objp;
{
	if (!xdr_string(xdrs, &objp->mon_name, SM_MAXSTRLEN)) {
		return (FALSE);
	}
	if (!xdr_my_id(xdrs, &objp->my_id)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_mon(xdrs, objp)
	XDR *xdrs;
	mon *objp;
{
	if (!xdr_mon_id(xdrs, &objp->mon_id)) {
		return (FALSE);
	}
	if (!xdr_opaque(xdrs, objp->priv, 16)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_sm_stat(xdrs, objp)
	XDR *xdrs;
	sm_stat *objp;
{
	if (!xdr_int(xdrs, &objp->state)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_res(xdrs, objp)
	XDR *xdrs;
	res *objp;
{
	if (!xdr_enum(xdrs, (enum_t *)objp)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_sm_stat_res(xdrs, objp)
	XDR *xdrs;
	sm_stat_res *objp;
{
	if (!xdr_res(xdrs, &objp->res_stat)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->state)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_status(xdrs, objp)
	XDR *xdrs;
	status *objp;
{
	if (!xdr_string(xdrs, &objp->mon_name, SM_MAXSTRLEN)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->state)) {
		return (FALSE);
	}
	if (!xdr_opaque(xdrs, objp->priv, 16)) {
		return (FALSE);
	}
	return (TRUE);
}

