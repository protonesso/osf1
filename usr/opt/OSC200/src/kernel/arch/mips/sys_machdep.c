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
static char	*sccsid = "@(#)$RCSfile: sys_machdep.c,v $ $Revision: 1.2.4.2 $ (DEC) $Date: 1992/04/14 13:35:10 $";
#endif 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)sys_machdep.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/mtio.h>
#include <sys/trace.h>


#ifdef TRACE
int	nvualarm;

vtrace(p, args, retval)
	struct proc *p;
	void *args;
	int *retval;
{
	register struct args {
		int	request;
		int	value;
	} *uap = (struct args *) args;
	int vdoualarm();
	int error = 0;

	switch (uap->request) {

	case VTR_DISABLE:		/* disable a trace point */
	case VTR_ENABLE:		/* enable a trace point */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
			error = EINVAL;
		else {
			*retval = traceflags[uap->value];
			traceflags[uap->value] = uap->request;
		}
		break;

	case VTR_VALUE:		/* return a trace point setting */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
			error = EINVAL;
		else
			*retval = traceflags[uap->value];
		break;

	case VTR_UALARM:	/* set a real-time ualarm, less than 1 min */
		if (uap->value <= 0 || uap->value > 60 * hz ||
		    nvualarm > 5)
			error = EINVAL;
		else {
			nvualarm++;
			timeout(vdoualarm, (caddr_t)p->p_pid,
			    uap->value);
		}
		break;

	case VTR_STAMP:
		trace(TR_STAMP, uap->value, p->p_pid);
		break;
	}
	return (error);
}

vdoualarm(arg)
	int arg;
{
	register struct proc *p;

	p = pfind(arg);
	if (p)
		psignal(p, 16);
	nvualarm--;
}
#endif /* TRACE */

#ifdef COMPAT
/*
 * Note: these tables are sorted by
 * ioctl "code" (in ascending order).
 */
int dctls[] = { DKIOCHDR, 0 };
int fctls[] = { FIOCLEX, FIONCLEX, FIOASYNC, FIONBIO, FIONREAD, 0 };
int mctls[] = { MTIOCTOP, MTIOCGET, 0 };
int tctls[] = {
	TIOCGETD, TIOCSETD, TIOCHPCL, TIOCMODG, TIOCMODS,
	TIOCGETP, TIOCSETP, TIOCSETN, TIOCEXCL, TIOCNXCL,
	TIOCFLUSH,TIOCSETC, TIOCGETC, TIOCREMOTE,TIOCMGET,
	TIOCMBIC, TIOCMBIS, TIOCMSET, TIOCSTART,TIOCSTOP,
	TIOCPKT,  TIOCNOTTY,TIOCSTI,  TIOCOUTQ, TIOCGLTC,
	TIOCSLTC, TIOCSPGRP,TIOCGPGRP,TIOCCDTR, TIOCSDTR,
	TIOCCBRK, TIOCSBRK, TIOCLGET, TIOCLSET, TIOCLBIC,
	TIOCLBIS, 0
};

/*
 * Map an old style ioctl command to new.
 */
mapioctl(cmd)
	int cmd;
{
	register int *map, c;

	switch ((cmd >> 8) & 0xff) {

	case 'd':
		map = dctls;
		break;

	case 'f':
		map = fctls;
		break;

	case 'm':
		map = mctls;
		break;

	case 't':
		map = tctls;
		break;

	default:
		return (0);
	}
	while ((c = *map) && (c&0xff) < (cmd&0xff))
		map++;
	if (c && (c&0xff) == (cmd&0xff))
		return (c);
	return (0);
}
#endif /* COMPAT */
