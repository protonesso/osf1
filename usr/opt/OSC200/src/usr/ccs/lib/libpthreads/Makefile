#
# *****************************************************************
# *                                                               *
# *    Copyright (c) Digital Equipment Corporation, 1991, 1994    *
# *                                                               *
# *   All Rights Reserved.  Unpublished rights  reserved  under   *
# *   the copyright laws of the United States.                    *
# *                                                               *
# *   The software contained on this media  is  proprietary  to   *
# *   and  embodies  the  confidential  technology  of  Digital   *
# *   Equipment Corporation.  Possession, use,  duplication  or   *
# *   dissemination of the software and media is authorized only  *
# *   pursuant to a valid written license from Digital Equipment  *
# *   Corporation.                                                *
# *                                                               *
# *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
# *   by the U.S. Government is subject to restrictions  as  set  *
# *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
# *   or  in  FAR 52.227-19, as applicable.                       *
# *                                                               *
# *****************************************************************
#
#
# HISTORY
#
#
#	@(#)$RCSfile: Makefile,v $ $Revision: 4.2.8.2 $ (DEC) $Date: 1993/03/15 20:55:55 $
# (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
# ALL RIGHTS RESERVED
#
#
# OSF/1 Release 1.0

VPATH		= ${target_machine}

LIBRARIES	= libpthreads_osf.a

EXPLIB_TARGETS	= export_libpthreads_osf.a

ILIST		= libpthreads_osf.a
IDIR		= /usr/ccs/lib/
IMODE		= 644

OFILES		= cond.o evt.o fork.o lib_lock.o malloc.o mutex.o \
		  pthread.o pthread_attr.o sched.o signal.o \
		  specific.o spin.o stack.o vp.o \
		  ${${TARGET_MACHINE}_OFILES}

include ${MAKEFILEPATH}/standard.mk
include ${MAKEFILEPATH}/libs.mk
include ${MAKEFILEPATH}/objects.mk
include ${target_machine}/machdep.mk
