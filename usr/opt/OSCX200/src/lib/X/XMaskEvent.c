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
/* $XConsortium: XMaskEvent.c,v 11.22 91/02/20 18:48:54 rws Exp $ */
/* Copyright    Massachusetts Institute of Technology    1986	*/

/*
Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation, and that the name of M.I.T. not be used in advertising or
publicity pertaining to distribution of the software without specific,
written prior permission.  M.I.T. makes no representations about the
suitability of this software for any purpose.  It is provided "as is"
without express or implied warranty.
*/

#define NEED_EVENTS
#include "Xlibint.h"

#if __STDC__
#define Const const
#else
#define Const /**/
#endif

extern _XQEvent *_qfree;
extern long Const _Xevent_to_mask[];
#define AllPointers (PointerMotionMask|PointerMotionHintMask|ButtonMotionMask)
#define AllButtons (Button1MotionMask|Button2MotionMask|Button3MotionMask|\
		    Button4MotionMask|Button5MotionMask)

/* 
 * return the next event in the queue matching one of the events in the mask.
 * If no event, flush output, and wait until match succeeds.
 * Events earlier in the queue are not discarded.
 */

XMaskEvent (dpy, mask, event)
	register Display *dpy;
	long mask;		/* Selected event mask. */
	register XEvent *event;	/* XEvent to be filled in. */
{
	register _XQEvent *prev, *qelt;

        LockDisplay(dpy);
	prev = NULL;
	while (1) {
	    for (qelt = prev ? prev->next : dpy->head;
		 qelt;
		 prev = qelt, qelt = qelt->next) {
		if ((qelt->event.type < LASTEvent) &&
		    (_Xevent_to_mask[qelt->event.type] & mask) &&
		    ((qelt->event.type != MotionNotify) ||
		     (mask & AllPointers) ||
		     (mask & AllButtons & qelt->event.xmotion.state))) {
		    *event = qelt->event;
		    if (prev) {
			if ((prev->next = qelt->next) == NULL)
			    dpy->tail = prev;
		    } else {
			if ((dpy->head = qelt->next) == NULL)
			dpy->tail = NULL;
		    }
		    qelt->next = _qfree;
		    _qfree = qelt;
		    dpy->qlen--;
		    UnlockDisplay(dpy);
		    return;
		}
	    }
	    _XReadEvents(dpy);
	}
}
