/*-------------------------------------------------------------------------
 *
 * parsetree.h
 *	  Routines to access various components and subcomponents of
 *	  parse trees.
 *
 *
 * Portions Copyright (c) 1996-2005, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $PostgreSQL: pgsql/src/include/parser/parsetree.h,v 1.29 2004/12/31 22:03:38 pgsql Exp $
 *
 *-------------------------------------------------------------------------
 */
#ifndef PARSETREE_H
#define PARSETREE_H

#include "nodes/parsenodes.h"
#include "nodes/pg_list.h"		/* for list_nth(), etc */


/* ----------------
 *		range table operations
 * ----------------
 */

/*
 *		rt_fetch
 *
 * NB: this will crash and burn if handed an out-of-range RT index
 */
#define rt_fetch(rangetable_index, rangetable) \
	((RangeTblEntry *) list_nth(rangetable, (rangetable_index)-1))

/*
 *		getrelid
 *
 *		Given the range index of a relation, return the corresponding
 *		relation OID.  Note that InvalidOid will be returned if the
 *		RTE is for a non-relation-type RTE.
 */
#define getrelid(rangeindex,rangetable) \
	(rt_fetch(rangeindex, rangetable)->relid)

/*
 * Given an RTE and an attribute number, return the appropriate
 * variable name or alias for that attribute of that RTE.
 */
extern char *get_rte_attribute_name(RangeTblEntry *rte, AttrNumber attnum);

/*
 * Given an RTE and an attribute number, return the appropriate
 * type and typemod info for that attribute of that RTE.
 */
extern void get_rte_attribute_type(RangeTblEntry *rte, AttrNumber attnum,
					   Oid *vartype, int32 *vartypmod);

/*
 * Check whether an attribute of an RTE has been dropped (note that
 * get_rte_attribute_type will fail on such an attr)
 */
extern bool get_rte_attribute_is_dropped(List *rtable, int rtindex,
							 AttrNumber attnum);


/* ----------------
 *		target list operations
 * ----------------
 */

extern TargetEntry *get_tle_by_resno(List *tlist, AttrNumber resno);

#endif   /* PARSETREE_H */