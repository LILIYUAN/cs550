/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "obtain.h"

bool_t
xdr_filename (XDR *xdrs, filename *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, objp, MAXNAME))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_request (XDR *xdrs, request *objp)
{
	register int32_t *buf;

	 if (!xdr_filename (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->seek_bytes))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_filedata (XDR *xdrs, filedata objp)
{
	register int32_t *buf;

	 if (!xdr_opaque (xdrs, objp, SIZE))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_datareceived (XDR *xdrs, datareceived *objp)
{
	register int32_t *buf;

	 if (!xdr_filedata (xdrs, objp->data))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->bytes))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_readfile_res (XDR *xdrs, readfile_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errno))
		 return FALSE;
	switch (objp->errno) {
	case 0:
		 if (!xdr_datareceived (xdrs, &objp->readfile_res_u.chunk))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}