//����ɽ�ɡ�mhxy-yushu 2001/2
//By tianlin@Mhxy for 2001.12.30/��Ϊ�Ϻ��Ǹ��ط�����̫����
inherit ROOM;
void create ()
{
  set ("short","С���");
  set ("long", @LONG

��ͷ������ȥ��ֻ��һ����ǽ���������飬һ��������СϪΧ��ʮ��
�䰫����é�ݣ�������ѻ�졣����֮�أ���������·�������̣���ѻ
����Ȼ�ش�ƫƧ��������������ϡ�������ĵ�������ĺ�ͯ����������
���˲��޻���֮�С������������ĿԶ��������������ɽ������
����������ȥ��
LONG);

  set("outdoors", 2);
  set("exits", ([ 
     "east" : "/d/gao/daotian2",
    "south" :  __DIR__"road1",
   ]));
 setup();
}





