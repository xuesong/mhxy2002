inherit ROOM;
void create ()
{
  set ("short", "ɽʯ·");
  set ("long", @LONG

һ����ʯ·��һ��Ũ�ҵ��ȷ紵���㶫�����ᣬ���������¾���
���������Ƿ�����ӿ���ҽ����㲻�����˸����䡣
LONG);

  set("exits", ([
        "northwest" : __DIR__"road4",
        "southeast" : __DIR__"road6",
      ]));
  set("outdoors", "mojiao");
  setup();
}