//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// rmdir.c

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
   string dir;

   if(!arg) return help(me);

   dir = resolve_path(me->query("cwd"), arg);

   seteuid(geteuid(me));
   if( rmdir(dir) )
     write("Ok.\n");
   else
     write("ɾ��ʧ�ܡ�\n");
   return 1;   
}

int help(object me)
{
   write(@HELP
ָ���ʽ : rmdir <��Ŀ¼��>

ɾ��һ����Ŀ¼��
HELP
   );
   return 1;
}