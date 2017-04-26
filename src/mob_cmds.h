#ifndef _MOB_CMDS_H_
#define _MOB_CMDS_H_
struct	mob_cmd_type
{
    char * const	name;
    DO_FUN *		do_fun;
};

struct obj_cmd_type
{
    char * const	name;
    OBJ_FUN *		obj_fun;
};

struct room_cmd_type
{
    char * const	name;
    ROOM_FUN *		room_fun;
};

/* the command table itself */
extern	const	struct	mob_cmd_type	mob_cmd_table	[];

/*
 * MOB command functions.
 * Defined in mob_cmds.c
 */
DECLARE_DO_FUN(	do_mpasound	);
DECLARE_DO_FUN(	do_mpgecho	);
DECLARE_DO_FUN(	do_mpzecho	);
DECLARE_DO_FUN(	do_mpkill	);
DECLARE_DO_FUN(	do_mpassist	);
DECLARE_DO_FUN(	do_mpjunk	);
DECLARE_DO_FUN(	do_mpechoaround	);
DECLARE_DO_FUN(	do_mpecho	);
DECLARE_DO_FUN(	do_mpechoat	);
DECLARE_DO_FUN(	do_mpmload	);
DECLARE_DO_FUN(	do_mpoload	);
DECLARE_DO_FUN(	do_mppurge	);
DECLARE_DO_FUN(	do_mpgoto	);
DECLARE_DO_FUN(	do_mpat		);
DECLARE_DO_FUN(	do_mptransfer	);
DECLARE_DO_FUN(	do_mpgtransfer	);
DECLARE_DO_FUN(	do_mpatransfer	);
DECLARE_DO_FUN(	do_mpforce	);
DECLARE_DO_FUN(	do_mpgforce	);
DECLARE_DO_FUN(	do_mpvforce	);
DECLARE_DO_FUN(	do_mpcast	);
DECLARE_DO_FUN(	do_mpdamage	);
DECLARE_DO_FUN(	do_mpremember	);
DECLARE_DO_FUN(	do_mpforget	);
DECLARE_DO_FUN(	do_mpdelay	);
DECLARE_DO_FUN(	do_mpcancel	);
DECLARE_DO_FUN(	do_mpcall	);
DECLARE_DO_FUN(	do_mpflee	);
DECLARE_DO_FUN(	do_mpotransfer	);
DECLARE_DO_FUN(	do_mpremove	);

/*
 * OBJcommand functions
 * Defined in mob_cmds.c
 */
DECLARE_OBJ_FUN( do_opgecho	 );
DECLARE_OBJ_FUN( do_opzecho	 );
DECLARE_OBJ_FUN( do_opecho	 );
DECLARE_OBJ_FUN( do_opechoaround );
DECLARE_OBJ_FUN( do_opechoat	 );
DECLARE_OBJ_FUN( do_opmload	 );
DECLARE_OBJ_FUN( do_opoload	 );
DECLARE_OBJ_FUN( do_oppurge	 );
DECLARE_OBJ_FUN( do_opgoto	 );
DECLARE_OBJ_FUN( do_optransfer	 );
DECLARE_OBJ_FUN( do_opgtransfer	 );
DECLARE_OBJ_FUN( do_opotransfer	 );
DECLARE_OBJ_FUN( do_opforce	 );
DECLARE_OBJ_FUN( do_opgforce	 );
DECLARE_OBJ_FUN( do_opvforce	 );
DECLARE_OBJ_FUN( do_opdamage	 );
DECLARE_OBJ_FUN( do_opremember	 );
DECLARE_OBJ_FUN( do_opforget	 );
DECLARE_OBJ_FUN( do_opdelay	 );
DECLARE_OBJ_FUN( do_opcancel	 );
DECLARE_OBJ_FUN( do_opcall	 );
DECLARE_OBJ_FUN( do_opremove	 );
DECLARE_OBJ_FUN( do_opattrib	 );

/*
 * ROOMcommand functions
 * Defined in mob_cmds.c
 */
DECLARE_ROOM_FUN( do_rpasound	 );
DECLARE_ROOM_FUN( do_rpgecho	 );
DECLARE_ROOM_FUN( do_rpzecho	 );
DECLARE_ROOM_FUN( do_rpecho	 );
DECLARE_ROOM_FUN( do_rpechoaround);
DECLARE_ROOM_FUN( do_rpechoat	 );
DECLARE_ROOM_FUN( do_rpmload	 );
DECLARE_ROOM_FUN( do_rpoload	 );
DECLARE_ROOM_FUN( do_rppurge	 );
DECLARE_ROOM_FUN( do_rptransfer	 );
DECLARE_ROOM_FUN( do_rpgtransfer );
DECLARE_ROOM_FUN( do_rpotransfer );
DECLARE_ROOM_FUN( do_rpforce	 );
DECLARE_ROOM_FUN( do_rpgforce	 );
DECLARE_ROOM_FUN( do_rpvforce	 );
DECLARE_ROOM_FUN( do_rpdamage	 );
DECLARE_ROOM_FUN( do_rpremember	 );
DECLARE_ROOM_FUN( do_rpforget	 );
DECLARE_ROOM_FUN( do_rpdelay	 );
DECLARE_ROOM_FUN( do_rpcancel	 );
DECLARE_ROOM_FUN( do_rpcall	 );
DECLARE_ROOM_FUN( do_rpremove	 );
#endif
