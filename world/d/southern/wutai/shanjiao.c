//by tianlin 2001.7.3

inherit ROOM;

void create()
{
set("short", "��̨ɽ����");
set("long", @LONG
    

�����Ӵ��Ա��ķ�Բ�������Ͷ�����̨ɽ�ˣ���������ɽ�壬
��幰�����࣬��ɽ�ȴ�����ϰϰ����ʹ���С��صĹ�������
�������������ɫ����ʩ�ɡ�

LONG );


set("exits", ([
  "northup"   : __DIR__"qinglianggu",
  "south"   : __DIR__"guandao1",
"northeast" : "/d/12gong/toby1",
]));


set("objects", ([
]));



set("outdoors", 1);

setup();
}