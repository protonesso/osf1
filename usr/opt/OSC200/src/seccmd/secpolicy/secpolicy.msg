$
$ *****************************************************************
$ *                                                               *
$ *    Copyright (c) Digital Equipment Corporation, 1991, 1994    *
$ *                                                               *
$ *   All Rights Reserved.  Unpublished rights  reserved  under   *
$ *   the copyright laws of the United States.                    *
$ *                                                               *
$ *   The software contained on this media  is  proprietary  to   *
$ *   and  embodies  the  confidential  technology  of  Digital   *
$ *   Equipment Corporation.  Possession, use,  duplication  or   *
$ *   dissemination of the software and media is authorized only  *
$ *   pursuant to a valid written license from Digital Equipment  *
$ *   Corporation.                                                *
$ *                                                               *
$ *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
$ *   by the U.S. Government is subject to restrictions  as  set  *
$ *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
$ *   or  in  FAR 52.227-19, as applicable.                       *
$ *                                                               *
$ *****************************************************************
$
$
$ HISTORY
$quote "
$set MS_SECPOLICY

ACLD_1	"Error on open of ACL logfile"
ACLD_2	"ACL: daemon initiated\n"
ACLD_3	"ACL: cannot find uid tcb.\n"
ACLD_4	"ACL: cannot find group tcb.\n"
ACLD_5	"Access control lists are configured.\n"
ACLD_6	"ACL: policy parameters: policy %d minor %d\n"
ACLD_7	"ACL: policy parameters: subj_tag %d obj_tag %d\n"
ACLD_8	"ACL: policy parameters: subj_tags %d obj_tags %d\n"
ACLD_9	"ACL: error on open of spd device"
ACLD_10	"ACL: error on init ioctl of spd device"
ACLD_11	"ACL: policy init routine called\n"
ACLD_12	"ACL: unable to malloc space for acl ir\n"
ACLD_13	"ACL: unable to malloc space for id ir\n"
ACLD_14	"ACL: message device initialization done\n"
ACLD_15	"ACL: error on database open"
ACLD_16	"ACL: database file opened\n"
ACLD_17	"ACL: Error on fork"
ACLD_18	"ACL: daemon process forked-process id %d\n"
ACLD_19	"ACL: error on EXCL ioctl"
ACLD_20	"ACL: daemon process text lock fail-%d\n"
ACLD_21	"ACL: daemon process text locked\n"
ACLD_22	"ACL: error or device read %d\n"
ACLD_23	"ACL: error on read of acl device"
ACLD_24	"ACL: invalid msg size %d\n"
ACLD_25	"ACL: message type: %d sync id: %d\n"
ACLD_26	"ACL: map tag for: %d %d length: %d\n"
ACLD_27	"ACL: unable to map ir to tag\n"
ACLD_28	"ACL: set tag: %x\n"
ACLD_29	"ACL: map subject tag for uid %d gid %d groups"
ACLD_30	"ACL: unable to map subj ir to tag\n"
ACLD_31	"ACL: set subject tag: %x\n"
ACLD_32	"ACL: get attr for: %x\n"
ACLD_33	"ACL: unable to map tag to ir\n"
ACLD_34	"ACL: decision on: subj tag: %x obj_tag: %x\n"
ACLD_35	"ACL: decision on: %d %d tag: %x\n"
ACLD_36	"ACL: can't map subject tag\n"
ACLD_37	"ACL: can't map object tag\n"
ACLD_38	"ACL: shutdown notify message\n"
ACLD_39	"ACL: shutdown message\n"
ACLD_40	"ACL: invalid message type %d\n"
ACLD_41	"ACL: no access permitted\n"
ACLD_42	"ACL: decision Read: %d Write: %d Exec: %d\n"
ACLD_43	"ACL: SIGTERM received for shutdown\n"
ACLD_44	"ACL: error on database reopen"
ACLD_45	"ACL: daemon reopened dbase for RDONLY\n"
ACLD_46	"Error on re-open of ACL log"
ACLD_47	"ACL: daemon opened new debug file\n"
ACLD_48	"ACL: bad system call\n"
DBCK_1	"%s: need sysadmin authorization\n"
DBCK_2	"%s: insufficient privileges\n"
DBCK_3	"usage: dbck [-y|-n] [-v] -f file\n"
DBCK_4	"Error opening debug file"
DBCK_5	"usage: dbck [-y|-n] [-v] -f file [-d debug]\n"
DBCK_6	"Error on spdbm_open() of %s\n"
DBCK_7	"\n\t*** Database Check for: %s *** \n\n"
DBCK_8	"Error on index page malloc\n"
DBCK_9	"\t*** Phase 1 Checking TAG to IR Mappings\n"
DBCK_10	"Error on index page read"
DBCK_11	"Error on index page write"
DBCK_12	"\t*** Phase 2 Checking IR to TAG Mappings\n"
DBCK_13	"\t*** Phase 3 Checking Index Value Ranges\n"
DBCK_14	"\t\tTAG Index page out of range-%d\n"
DBCK_15	"Error on tag index page read"
DBCK_16	"\t\tIR Index page out of range-%d\n"
DBCK_17	"\n\t*** Tag Count: %d, Tags Unmatched: %d\n"
DBCK_18	"\t*** IR  Count: %d, IRs  Unmatched: %d\n"
DBCK_19	"Error on data page read"
DBCK_20	"\t\tIncorrect Page Type, Clear? "
DBCK_21	"Error on re-write of index page"
DBCK_22	"Error on page remalloc\n"
DBCK_23	"\t\tBad TAG DATAPAGE Format: %d-%d, Clear? "
DBCK_24	"\t\tMissing IR for TAG: %x, Insert IR? "
DBCK_25	"\t\tFailed Insert, Clear? "
DBCK_26	"\t\tClear? "
DBCK_27	"Failed to Clear Entry\n"
DBCK_28	"\t\tBad IR DATAPAGE Format: %d-%d, Clear? "
DBCK_29	"\t\tMissing TAG for IR: %x, Insert TAG? "
DBCK_ACL_1	"Error on debug file open"
DBCK_ACL_2	"\n*** Primary index partition mappings. ***\n\n"
DBCK_ACL_3	"Error on read of tag"
DBCK_ACL_4	"\n*** Alternate index partition mappings. ***\n\n"
DBCK_ACL_5	"IR for tag %x too big (%d bytes)\n"
DBCK_ACL_6	"Error on read of ir"
DBCK_ACL_7	"Error on ir conversion for %x\n"
DBCK_ACL_8	"Tag: %8x	u %hd %hd g %hd %hd m 0%o Label: %s\n"
DBCK_ACL_9	"Tag: %8x	Label: %s\n"
DBCK_ACL_10	"uid %d,"
DBCK_ACL_11	"gid %d "
DBCK_ACL_12     "IPC ACCESS ACL: Tag %8x cuid %hd uid %hd cgid %hd gid %hd Label:\n%s\n"
DBCK_ACL_13     "ACCESS ACL: Tag %8x uid %hd gid %hd Label:\n%s\n"
DBCK_ACL_14     "DEFAULT ACL: Tag %8x Label:\n%s\n "
DBCK_ACL_15     "UNKNOWN ACL TYPE: Tag %8x cuid %hd uid %hd cgid %hd gid %hd Label:\n%s\n"
DBCK_MAC_1	"Error on debug file open"
DBCK_MAC_2	"\n*** Primary index partition mappings. ***\n\n"
DBCK_MAC_3	"Error on read of tag"
DBCK_MAC_4	"\n*** Alternate index partition mappings. ***\n\n"
DBCK_MAC_5	"Error on read of ir"
DBCK_MAC_6	"Error on ir conversion for %x\n"
DBCK_MAC_7	"Tag: %x	Label: %s\n"
MACILBD_1	"Error on open of MAC logfile"
MACILBD_2	"MAC: daemon initiated\n"
MACILBD_3	"MAC daemon: cannot find uid tcb.\n"
MACILBD_4	"MAC daemon: cannot find group tcb.\n"
MACILBD_5	"Mandatory access control is configured.\n"
MACILBD_6	"Information labels are configured.\n"
MACILBD_7	"MAC: policy parameters: policy %d minor %d\n"
MACILBD_8	"MAC: policy parameters: subj_tag %d obj_tag %d\n"
MACILBD_9	"MAC: policy parameters: subj_tags %d obj_tags %d\n"
MACILBD_10	"MAC daemon: error on open of spd device"
MACILBD_11	"MAC daemon: error on SPIOC_INIT of policy"
MACILBD_12	"MAC: policy init routine called\n"
MACILBD_13	"MAC daemon: unable to alloc space for subject ir\n"
MACILBD_14	"MAC daemon: unable to alloc space for object ir\n"
MACILBD_15	"MAC daemon: unable to alloc space for combination ir\n"
MACILBD_16	"MAC daemon: unable to malloc space for System Lo ir\n"
MACILBD_17	"MAC daemon: unable to malloc space for System Hi ir\n"
MACILBD_18	"MAC: message device initialization done\n"
MACILBD_19	"MAC daemon: error on database open"
MACILBD_20	"MAC: database file opened\n"
MACILBD_21	"MAC daemon: Error on fork"
MACILBD_22	"MAC: daemon process forked-process id %d\n"
MACILBD_23	"MAC daemon: error on EXCL ioctl"
MACILBD_24	"MAC: daemon process text lock fail-%d\n"
MACILBD_25	"MAC: daemon process text locked\n"
MACILBD_26	"MAC: device read error %d\n"
MACILBD_27	"MAC daemon: error on read of mac device"
MACILBD_28	"MAC: read size error %d\n"
MACILBD_29	"MAC message type: %d sync id: %d\n"
MACILBD_30	"MAC System IR map tag-%d\n"
MACILBD_31	"MAC set tag error EBADIREP\n"
MACILBD_32	"MAC daemon: unable to map ir to tag\n"
MACILBD_33	"MAC set tag error EFULLDB\n"
MACILBD_34	"MAC set tag: %x\n"
MACILBD_35	"MAC system attribute %x\n"
MACILBD_36	"MAC get attr for: %x\n"
MACILBD_37	"MAC daemon: unable to map tag to ir\n"
MACILBD_38	"MAC get attribute OK-size %d\n"
MACILBD_39	"MAC decision: subj: %x obj: %x\n"
MACILBD_40	"MAC daemon: unable to map subject tag\n"
MACILBD_41	"MAC decision error ENOSUBJTAG\n"
MACILBD_42	"MAC daemon: unable to map object tag\n"
MACILBD_43	"MAC decision error ENOOBJTAG\n"
MACILBD_44	"MAC: shutdown notify message\n"
MACILBD_45	"MAC: shutdown message\n"
MACILBD_46	"MAC: invalid message type %d\n"
MACILBD_47	"Subj IR (%d bytes): "
MACILBD_48	"Obj IR (%d bytes):  "
MACILBD_49	"MAC decision: SDOM: %d ODOM: %d SAME: %d INCOMP: %d\n"
MACILBD_50	"ILB decision: SDOM: %d ODOM: %d SAME: %d"
MACILBD_51	" NOCOMB: %d Tag: %x\n"
MACILBD_52	"MAC daemon: unable to map combined ILB to tag\n"
MACILBD_53	"MAC can't map ILB combination to tag\n"
MACILBD_54	"MAC valid label range check succeeded\n"
MACILBD_55	"MAC daemon: SIGTERM received for shutdown\n"
MACILBD_56	"MAC daemon: error on database reopen"
MACILBD_57	"MAC daemon: reopened database for RDONLY\n"
MACILBD_58	"Error on re-open of MAC logfile"
MACILBD_59	"MAC daemon: opened new debug file\n"
MACILBD_60	"MAC daemon: bad system call\n"
MKDB_1	"Usage: mkdb filename pagesize threshold [blocks]\n"
MKDB_2	"Error on open"
MKDB_3	"Unable to locate password entry for tcb\n"
MKDB_4	"Unable to locate group entry for tcb\n"
MKDB_4A "Pagesize must be at least 1024\n"
MKDB_5	"Threshold percentage should be in the range 20 - 80\n"
MKDB_6	"\n\n\t*** Security Policy Database Initialization ***\n\n"
MKDB_7	"\t\tDatabase Name:\t\t%s\n"
MKDB_8	"\t\tIndex Page Size:\t%d\n"
MKDB_9	"\t\tData Page Size:\t\t%d\n"
MKDB_10	"\t\tPage Threshold:\t\t%d\n"
MKDB_11	"\t\tHigh Offset:\t\t%d (%x)\n"
MKDB_12	"\t\tLevel 2 Size:\t\t%d\n"
MKDB_13	"Error on initializing control pages."
MKDB_14	"Error on initializing remainder of control pages."
SPDBM_1	"spdbm: error on database open"
SPDBM_2	"spdbm: error on database header read"
SPDBM_3	"spdbm: error on database tag level1 read"
SPDBM_4	"spdbm: error on database ir level1 read"
SPDBM_5	"spdbm: error on database single level free read"
SPDBM_6	"spdbm: error on database multi-level free read"
SPDBM_7	"spdbm: error on level2 page mask malloc\n"
SPDBM_8	"spdbm: error on database level2 mask page read"
SPDBM_9	"spdbm: error on tag cache malloc\n"
SPDBM_10	"spdbm: error on page cache malloc\n"
SPDBM_11	"spdbm: error on malloc of buffer control block\n"
SPDBM_12	"spdbm: error on buffer pool malloc\n"
SPDBM_13	"spdbm: error on database reopen"
SPDBM_14	"***** TAG INSERT: %x *****\n"
SPDBM_15	"spdbm: duplicate key on insert\n"
SPDBM_16	"spdbm: error on l2 mask flush"
SPDBM_17	"***** IR INSERT *****\n"
SPDBM_18	"***** TAG DELETE *****\n"
SPDBM_19	"spdbm: unable to malloc for ir delete\n"
SPDBM_20	"spdbm: error on flush from delete"
SPDBM_21	"***** IR DELETE *****\n"
SPDBM_22	"TCACHE Hit: daddr: %x\n"
SPDBM_23	"PCACHE Datapage Hit: addr: %x\n"
SPDBM_24	"PCACHE Miss 1: slot: %x addr: %x daddr: %x\n"
SPDBM_25	"LEVEL1 allocate: slot: %x addr: %x daddr: %x\n"
SPDBM_26	"spdbm: error on hdr flush"
SPDBM_27	"PCACHE Miss 2: slot: %x addr: %x daddr: %x\n"
SPDBM_28	"LEVEL2 Slot: %x\n"
SPDBM_29	"LEVEL2 allocate: slot: %x addr: %x daddr: %x\n"
SPDBM_30	"PCACHE Miss 3: slot: %x addr: %x daddr: %x\n"
SPDBM_31	"LOCATE OK: addr: %x daddr: %x\n"
SPDBM_32	"IR LEVEL1 allocate: slot: %x addr: %x daddr: %x\n"
SPDBM_33	"IR PCACHE Miss 2: slot: %x addr: %x daddr: %x\n"
SPDBM_34	"IR LEVEL2 Slot: %x\n"
SPDBM_35	"IR LEVEL2 allocate: slot: %x addr: %x daddr: %x\n"
SPDBM_36	"IR PCACHE Miss 3: slot: %x addr: %x daddr: %x\n"
SPDBM_37	"IR LOCATE OK: addr: %x daddr: %x\n"
SPDBM_38	"spdbm: no level 2 page located for extend\n"
SPDBM_39	"tcache_insert addr: %x daddr: %x\n"
SPDBM_40	"\n\t*** Tag Cache Dump ***\n\n"
SPDBM_41	"Slot: %d Bucket: %d Daddr: %x Tag1: %x Tag2: %x\n"
SPDBM_42	"pcache_insert addr: %x daddr: %x\n"
SPDBM_43	"\n\t*** Page Cache Dump ***\n\n"
SPDBM_44	"Slot: %d Bucket: %d Daddr: %x Addr: %x\n"
SPDBM_45	"READ: on page: %x into addr: %x\n"
SPDBM_46	"spdbm: error on database read"
SPDBM_47	"MULTI READ: on page: %x into addr: %x for %d\n"
SPDBM_48	"WRITE: page: %x from addr: %x for %d\n"
SPDBM_49	"spdbm: I/O error on page write"
SPDBM_50	"page_lock: addr %x\n"
SPDBM_51	"spdbm: cannot locate page to lock\n"
SPDBM_52	"page_release: addr %x\n"
SPDBM_53	"spdbm: all pages locked on allocate\n"
SPDBM_54	"spdbm: no memory on malloc\n"
SPDBM_55	"spdbm: all multi-extent pages locked on alloc\n"
SPDBM_56	"spdbm: unable to locate control block entry on buffer free\n"
SPDBM_57	"spdbm: error on sfree flush"
SPDBM_58	"spdbm: error on dbase hdr flush for sfree"
SPDBM_59	"spdbm: error on mfree flush"
SPDBM_60	"spdbm: error on dbase hdr flush for mfree"
SPDBM_61	"spdbm: slevel free list overflow\n"
SPDBM_62	"spdbm: mlevel free list overflow\n"
SPDBM_63	"spdbm: error on sfree flush in block free"
SPDBM_64	"spdbm: error on mfree flush in block free"
SPDBM_65	"spdbm: unable to map buffer into disk block address\n"
SPDINIT_1	"Policy daemon spawner: cannot find uid tcb.\n"
SPDINIT_2	"Policy daemon spawner: cannot find group tcb.\n"
SPDINIT_3	"Policy daemon spawner: error on config file open"
SPDINIT_4	"Policy daemon spawner: Error on fork of policy"
SPDINIT_5	"Daemon %s terminated abnormally\n"
SPDINIT_6	"Daemon %s terminated by signal %d\n"
SPDINIT_7	"Policy daemon spawner: execlp() failed on policy daemon"
SPDINIT_8	"Policy daemon spawner: bad system call\n"
