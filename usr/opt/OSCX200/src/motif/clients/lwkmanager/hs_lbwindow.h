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
/*
** Generated by ODL Version X0.1 on Tue Jul 14 11:01:24 1992
*/

/*
** COPYRIGHT (c) 1989 BY
** DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASSACHUSETTS.
** ALL RIGHTS RESERVED.
**
** THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND COPIED
** ONLY  IN  ACCORDANCE  OF  THE  TERMS  OF  SUCH  LICENSE  AND WITH THE
** INCLUSION OF THE ABOVE COPYRIGHT NOTICE. THIS SOFTWARE OR  ANY  OTHER
** COPIES THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY
** OTHER PERSON.  NO TITLE TO AND  OWNERSHIP OF THE  SOFTWARE IS  HEREBY
** TRANSFERRED.
**
** THE INFORMATION IN THIS SOFTWARE IS  SUBJECT TO CHANGE WITHOUT NOTICE
** AND  SHOULD  NOT  BE  CONSTRUED  AS A COMMITMENT BY DIGITAL EQUIPMENT
** CORPORATION.
**
** DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE  OR  RELIABILITY OF ITS
** SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.
*/

/*
** Private Type Definitions for the LbWindow Object
*/

/*
** Abstract Type Definitions for subtypes of Object
*/

typedef _Object _List, _PtrTo _ListPtr;
typedef _Object _Window, _PtrTo _WindowPtr;
typedef _Object _EnvWindow, _PtrTo _EnvWindowPtr;
typedef _Object _HsObject, _PtrTo _HsObjectPtr;
typedef _Object _EnvContext, _PtrTo _EnvContextPtr;

/*
** LbWindow Instance Structure Definition
*/

typedef struct __LbWindow {
        _Type type;
        _Position x;
        _Position y;
        _Cardinal width;
        _Cardinal height;
        lwk_dxm_ui lwk_ui;
        _AnyPtr   display_data;
        _StateFlags flags;
        struct __Window *nextwindow;
        _HsObject linkbase;
        _AnyPtr private_data;
        struct __LbWindow *next;
    } _LbWindowInstance, _PtrTo _LbWindow, _PtrTo _PtrTo _LbWindowPtr;

/*
** LbWindow Property Name Table Index Definitions
*/

#define _LinkbaseIndex 0
#define _P_PrivateData "$PrivateData"
#define _PrivateDataIndex 1
#define _P_Next "$Next"
#define _NextIndex 2

/*
** LbWindow Property Name Table Definition
*/

#define _LbWindowPropertyNameTable \
    _PropertyNameTableEntry _Constant LbWindowPropertyNameTable[] = { \
        {_P_Linkbase, _LinkbaseIndex, _True}, \
        {_P_PrivateData, _PrivateDataIndex, _False}, \
        {_P_Next, _NextIndex, _False}, \
        {(_String) 0, 0, _False} \
    }

/*
** LbWindow Property Accessor Definitions
*/

#define _Linkbase_of(Obj) ((_LbWindow) _Reference(Obj))->linkbase
#define _PrivateData_of(Obj) ((_LbWindow) _Reference(Obj))->private_data
#define _Next_of(Obj) ((_LbWindow) _Reference(Obj))->next

/*
** Include Generic Operation Support
*/

#include "hs_operation_prototypes.h"

/*
** LbWindow Method Declarations
*/

_DeclareFunction(_Void EnvOpObjIllOp, (_in _Object object));
_DeclareFunction(_Void EnvOpLbWindowClear, (_inout _LbWindow window));
_DeclareFunction(_Void EnvOpLbWindowClose, (_inout _LbWindow window,
    _in _Boolean recycle));
_DeclareFunction(_Void EnvOpLbWindowCollapse, (_in _LbWindow window,
    _in _AnyPtr user_data));
_DeclareFunction(_LbWindow EnvOpObjCopy, (_in _LbWindow object));
_DeclareFunction(_LbWindow EnvOpObjCreate, (_in _Type type));
_DeclareFunction(_LbWindow EnvOpLbWindowCreate, (
    _in _Type type, _in _Cardinal width, _in _Cardinal height,
    _in _Position x, _in _Position y, _in _Widget parent));
_DeclareFunction(_LbWindow EnvOpWindowCreate, (_in _Type type));
_DeclareFunction(_Void EnvOpObjDelete, (_inout _LbWindow object));
_DeclareFunction(_Void EnvOpLbWindowDisplay, (_inout _LbWindow window,
    _in _HsObject linkbase));
_DeclareFunction(_Void EnvOpWindowDisplayMessage, (_in _LbWindow window,
    _Status *status, _Integer count));
_DeclareFunction(_Void EnvOpLbWindowExpand, (_in _LbWindow window,
    _in _AnyPtr user_data));
_DeclareFunction(_Void EnvOpLbWindowFree, (_inout _LbWindow object));
_DeclareFunction(_EnvWindow EnvOpWindowGetEnvWindow, (_in _LbWindow window));
_DeclareFunction(_Boolean EnvOpWindowGetSelection, (
    _in _LbWindow window, _in _GetSelectOperation operation,
    _inout _AnyPtr user_data));
_DeclareFunction(_Void EnvOpLbWindowGetValue, (_in _LbWindow object,
    _in _String property_name, _in _Domain domain,
    _in _AnyPtr value));
_DeclareFunction(_Void EnvOpWindowHighlight, (_in _LbWindow window,
    _in _HsObject hs_object));
_DeclareFunction(_Void EnvOpLbWindowInitialize, (_inout _LbWindow object,
    _in _LbWindow proto_object));
_DeclareFunction(_Boolean EnvOpObjIsType, (_in _LbWindow object, _in _Type type));
_DeclareFunction(_Boolean EnvOpLbWindowLbInWindow, (_out _LbWindow *window,
    _in lwk_linkbase linkbase));
_DeclareFunction(_LbWindow EnvOpLbWindowOpen, (_in _Type type, _in _Cardinal width,
    _in _Cardinal height, _in _Position x, _in _Position y,
    _in _Widget parent));
_DeclareFunction(_Void EnvOpWindowPositionWindow, (_in _LbWindow window));
_DeclareFunction(_Void EnvOpWindowRaiseWindow, (_in _LbWindow window));
_DeclareFunction(_Void EnvOpWindowSelect, (_in _LbWindow window,
    _in _HsObject hs_object));
_DeclareFunction(_Void EnvOpWindowSetCursor, (_in _LbWindow window,
    _in _CursorType cursor_type));
_DeclareFunction(_Void EnvOpLbWindowSetValue, (_inout _LbWindow object,
    _in _String property_name, _in _Domain domain,
    _in _AnyPtr value, _in _SetFlag flag));
_DeclareFunction(_Boolean EnvOpWindowSetWindowState, (
    _inout _LbWindow window, _in _WindowState state,
    _in _StateOperation operation));
_DeclareFunction(_Void EnvOpLbWindowUpdate, (_in _LbWindow window,
    _HsObject hs_object, _UpdateOperation update));

/*
** LbWindow Type Instance Definition
*/

#define _LbWindowTypeInstance \
    _TypeInstance _Constant HS__LbWindowTypeInstance = { \
        &HS__WindowTypeInstance, \
        sizeof(_LbWindowInstance), \
        { \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpLbWindowClear, \
        (_Method) EnvOpLbWindowClose, \
        (_Method) EnvOpLbWindowCollapse, \
        (_Method) EnvOpObjCopy, \
        (_Method) EnvOpObjCreate, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpLbWindowCreate, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpWindowCreate, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjDelete, \
        (_Method) EnvOpLbWindowDisplay, \
        (_Method) EnvOpWindowDisplayMessage, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpLbWindowExpand, \
        (_Method) EnvOpLbWindowFree, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpWindowGetEnvWindow, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpWindowGetSelection, \
        (_Method) EnvOpLbWindowGetValue, \
        (_Method) EnvOpWindowHighlight, \
        (_Method) EnvOpLbWindowInitialize, \
        (_Method) EnvOpObjIsType, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpLbWindowLbInWindow, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpLbWindowOpen, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpWindowPositionWindow, \
        (_Method) EnvOpWindowRaiseWindow, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpWindowSelect, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpWindowSetCursor, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpLbWindowSetValue, \
        (_Method) EnvOpWindowSetWindowState, \
        (_Method) EnvOpObjIllOp, \
        (_Method) EnvOpLbWindowUpdate \
        } \
    }

#define _LbWindowType \
    _Type _Constant HS__LbWindowType = &HS__LbWindowTypeInstance