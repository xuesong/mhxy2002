// COMMAND who1.c
// Last modified by zeus@����Ц Dec.30 1999

inherit F_CLEAN_UP;
#include <ansi.h>
int main(object me, string str)
{
    object where, ob, *ob_list;
    int i;
    string stri;
    seteuid(getuid());

    ob_list = users();
    ob_list = sort_array(users(), "sort_user", this_object());
    str = HIG"�������(ID)       ��Ѫ      ����      ����      ��ѧ���� ����   Ǳ��\n"NOR;
    str += "������������������������������������������������������������������������������������\n";
    for(i=0; i<sizeof(ob_list); i++)
    {
        ob = ob_list[i];
        where = environment(ob);

        str += sprintf(HIW"%-16s:  ",ob->name()+"("+ob->query("id")+")");
        str += sprintf(HIG"%-4d/%-4d ", ob->query("kee"), ob->query("max_kee"));
        str += sprintf(HIG"%-4d/%-4d ", ob->query("sen"), ob->query("max_sen"));
        str += sprintf(HIW"%-4d/%-4d ", ob->query("force"), ob->query("max_force"));
        str += sprintf(HIB"%-7d ", ob->query("combat_exp"));
        str += sprintf(HIM"%-7d ", ob->query("daoxing"));
        str += sprintf(HIC"%-3d \n"NOR, ob->query("potential"));
    }
    str += "������������������������������������������������������������������������������������\n";
    str = sprintf("%s���� %d λʹ���������С�\n", str, sizeof(ob_list));
    me->start_more(str);
    return 1;
}
int sort_user(object ob1, object ob2)
{
	if( wizardp(ob1) && !wizardp(ob2) ) return -1;
	if( wizardp(ob2) && !wizardp(ob1) ) return 1;
	if( wizardp(ob1) && wizardp(ob2) )
		return (int)SECURITY_D->get_wiz_level(ob2) 
			- (int)SECURITY_D->get_wiz_level(ob1);
	
	return (int)ob2->query("combat_exp") - (int)ob1->query("combat_exp");
}
int help(object me)
{
        write(@HELP
ָ���ʽ��who1

�����Ϣ��ѯ��
HELP
        );
        return 1;
}