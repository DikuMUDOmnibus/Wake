#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "merc.h"
#include "recycle.h"

BAN_DATA *ban_list;

void save_bans(void)
{
    BAN_DATA *pban;
    FILE *fp;
    bool found = false;

    fclose(fpReserve);
    if ( ( fp = fopen(BAN_FILE,"w") ) == NULL )
        perror(BAN_FILE);

	for (pban = ban_list; pban != NULL; pban = pban->next)
	{
		if (IS_SET(pban->ban_flags,BAN_PERMANENT))
		{
			found = true;
			fprintf(fp,"%-20s %-2d %s\n",pban->name,pban->level,
			print_flags(pban->ban_flags));
		}
	}

	fclose(fp);
	fpReserve = fopen( NULL_FILE, "r" );
	if (!found)
		unlink(BAN_FILE);
}

void load_bans(void){
	return;
    FILE *fp;
    BAN_DATA *ban_last;
 
	if ( ( fp = fopen( BAN_FILE, "r" ) ) == NULL )
		return;
 
	ban_last = NULL;
	for ( ; ; )
	{
		BAN_DATA *pban;
		if ( feof(fp) )
		{
			fclose( fp );
			return;
		}

		pban = new_ban();

		pban->name = str_dup(fread_word(fp));
		pban->level = fread_number(fp);
		pban->ban_flags = fread_flag(fp);
		fread_to_eol(fp);

		if (ban_list == NULL)
			ban_list = pban;
		else
			ban_last->next = pban;
		ban_last = pban;
	}
}

bool check_ban(char *site,int type)
{
    BAN_DATA *pban;
    char host[MSL];

    strcpy(host,capitalize(site));
    host[0] = LOWER(host[0]);

    for ( pban = ban_list; pban != NULL; pban = pban->next ) 
    {
		if(!IS_SET(pban->ban_flags,type))
			continue;

		if (IS_SET(pban->ban_flags,BAN_PREFIX) && IS_SET(pban->ban_flags,BAN_SUFFIX) && strstr(pban->name,host) != NULL)
			return true;

		if (IS_SET(pban->ban_flags,BAN_PREFIX) && !str_suffix(pban->name,host))
			return true;

		if (IS_SET(pban->ban_flags,BAN_SUFFIX) && !str_prefix(pban->name,host))
			return true;
    }

    return false;
}

void ban_site(CHAR_DATA *ch, char *argument, bool fPerm)
{
    char buf[MSL],buf2[MSL];
    char arg1[MAX_INPUT_LENGTH], arg2[MAX_INPUT_LENGTH];
    char *name;
    BUFFER *buffer;
    BAN_DATA *pban, *prev;
    bool prefix = false,suffix = false;
    int type;

    argument = one_argument(argument,arg1);
    argument = one_argument(argument,arg2);

    if ( arg1[0] == '\0' )
    {
		if (ban_list == NULL)
		{
			send_to_char("No sites banned at this time.\n\r",ch);
			return;
  		}
		buffer = new_buf();

        add_buf(buffer,"Banned sites  level  type     status\n\r");
        for (pban = ban_list;pban != NULL;pban = pban->next)
        {
			sprintf(buf2,"%s%s%s",
				IS_SET(pban->ban_flags,BAN_PREFIX) ? "*" : "",
				pban->name,
				IS_SET(pban->ban_flags,BAN_SUFFIX) ? "*" : "");
			sprintf(buf,"%-12s    %-3d  %-7s  %s\n\r",
				buf2,
				pban->level,
				IS_SET(pban->ban_flags,BAN_NEWBIES) ? "newbies" : IS_SET(pban->ban_flags,BAN_PERMIT)  ? "permit"  : IS_SET(pban->ban_flags,BAN_ALL) ? "all"	: "",
	    		IS_SET(pban->ban_flags,BAN_PERMANENT) ? "perm" : "temp");
			add_buf(buffer,buf);
        }

		page_to_char( buf_string(buffer), ch );
		free_buf(buffer);
		return;
	}

	/* find out what type of ban */
	if (arg2[0] == '\0' || !str_prefix(arg2,"all"))
		type = BAN_ALL;
	else if (!str_prefix(arg2,"newbies"))
		type = BAN_NEWBIES;
	else if (!str_prefix(arg2,"permit"))
		type = BAN_PERMIT;
	else
	{
		send_to_char("Acceptable ban types are all, newbies, and permit.\n\r",ch);
		return;
	}

	name = arg1;

	if (name[0] == '*')
	{
		prefix = true;
		name++;
	}

	if (name[strlen_color(name) - 1] == '*')
	{
		suffix = true;
		name[strlen_color(name) - 1] = '\0';
	}

	if (strlen_color(name) == 0)
	{
		send_to_char("You have to ban SOMETHING.\n\r",ch);
		return;
	}

	prev = NULL;
	for ( pban = ban_list; pban != NULL; prev = pban, pban = pban->next )
	{
		if (!str_cmp(name,pban->name))
		{
			if (pban->level > get_trust(ch))
			{
				send_to_char( "That ban was set by a higher power.\n\r", ch );
				return;
			}
			else
			{
				if (prev == NULL)
					ban_list = pban->next;
				else
					prev->next = pban->next;
				free_ban(pban);
			}
		}
	}

	pban = new_ban();
	pban->name = str_dup(name);
	pban->level = get_trust(ch);

	/* set ban type */
	pban->ban_flags = type;

	if (prefix)
		SET_BIT(pban->ban_flags,BAN_PREFIX);
	if (suffix)
		SET_BIT(pban->ban_flags,BAN_SUFFIX);
	if (fPerm)
		SET_BIT(pban->ban_flags,BAN_PERMANENT);

	pban->next  = ban_list;
	ban_list    = pban;
	save_bans();
	printf_to_char(ch,"%s has been banned.\n\r",pban->name);
	return;
}

void do_ban(CHAR_DATA *ch, char *argument)
{
    ban_site(ch,argument,false);
}

void do_permban(CHAR_DATA *ch, char *argument)
{
    ban_site(ch,argument,true);
}

void do_allow( CHAR_DATA *ch, char *argument )                        
{
	char arg[MIL];
	BAN_DATA *prev;
	BAN_DATA *curr;

	one_argument( argument, arg );

	if ( arg[0] == '\0' )
	{
		send_to_char( "Remove which site from the ban list?\n\r", ch );
		return;
	}

	prev = NULL;
	for ( curr = ban_list; curr != NULL; prev = curr, curr = curr->next )
	{
		if ( !str_cmp( arg, curr->name ) )
		{
			if (curr->level > get_trust(ch))
			{
				send_to_char("You are not powerful enough to lift that ban.\n\r",ch);
				return;
			}
			if ( prev == NULL )
				ban_list   = ban_list->next;
			else
				prev->next = curr->next;

			free_ban(curr);
			printf_to_char(ch,"Ban on %s lifted.\n\r",arg);
			save_bans();
			return;
		}
	}

	send_to_char( "Site is not banned.\n\r", ch );
	return;
}