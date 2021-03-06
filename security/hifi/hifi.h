/*
 * Structure definitions for the Hi-Fi provenance system
 *
 * Copyright (C) 2013 The Pennsylvania State University
 * Systems and Internet Infrastructure Security Laboratory
 *
 * Author: Devin J. Pohly <djpohly@cse.psu.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 */

#ifndef _SECURITY_HIFI_H
#define _SECURITY_HIFI_H


#include <linux/types.h>
#include <linux/xattr.h>
#include <linux/uuid.h>

#include "hifi_proto.h"


/* Key names for xattrs */
#define XATTR_HIFI_SUFFIX "hifi"
#define XATTR_NAME_HIFI XATTR_SECURITY_PREFIX XATTR_HIFI_SUFFIX

/* IP options number */
#define IPOPT_HIFI 0x9e


/*
 * Security label for struct cred.  "Opaque" processes are such that credentials
 * they fork are considered part of the original process, so we use a reference
 * counter to make sure these are freed at the appropriate time and no earlier.
 */
struct cred_security {
	struct kref refcount;
	u32 csid;
	int flags;
#define CSEC_INITED (1 << 0)
#define CSEC_OPAQUE (1 << 1)
};


/*
 * Security label for filesystems via struct super_block.  This UUID is stored
 * in the xattr of the root inode for persistence.  If we encounter a filesystem
 * with no such label, we create one and store it ourselves.
 */
struct sb_security {
	uuid_be uuid;
};


/* Security structures for XSI IPC */
struct msg_security {
	u32 msgid;
};

struct shm_security {
	u32 shmid;
};


/* Security structures for sockets */
struct sock_security {
	struct host_sockid full_id;
	struct sockid short_id;
	u8 full_set;
	u8 short_set;
};

struct skb_security {
	struct host_sockid id;
	u8 set;
};


/* Label option for IP */
struct sockid_opt {
	u8 num;
	u8 len;
	struct host_sockid label;
} __attribute__((packed));


#endif
