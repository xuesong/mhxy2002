// created by wxb 12/24/1998
// room: /d/qujing/huangfeng/cangjing.c

inherit ROOM;

void create ()
{
  set ("short", "����");
  set ("long", @LONG

�����ﶫ���������һ����񣬹������Ÿ��־��ķ�䡣����
��һ�鰸�����Ϸ���һ�����顣��ҳ���ƺ�д�š�����������
��С�֡�

LONG);

  set("exits", ([
        "south"    : __DIR__"jiangtang",
      ]));

  set("objects", ([
      ]));
  setup();
}
