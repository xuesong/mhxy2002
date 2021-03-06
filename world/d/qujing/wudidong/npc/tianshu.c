// guanjia.c
// 9-2-97 pickle

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int rank_me();
string expell_me(object me);
void create()
{
  set_name("田鼠精", ({"tian shu", "tian", "shu", "tianshu", "monster"}));
  set("gender", "女性");
  set("age", 23);
  set("long",
"她就是无底洞的大管家。想当年她和玉鼠一齐修仙成了人形，\n"
"但因资质太差，成正果终究是无望。照顾着当年的交情，玉鼠\n"
"安排她做了这洞的管家。\n");
  set("title", "大管家");
  set("cor", 25);
  set("combat_exp", 400000);
  set("daoxing", 600000);

  set("attitude", "heroic");
  create_family("陷空山无底洞", 2, "弟子");
  set_skill("literate", 120);
  set_skill("unarmed", 120);
  set_skill("parry", 120);
  set_skill("spells", 120);  
  set_skill("sword", 120);  
  set_skill("qixiu-jian", 120);
  set_skill("yinfeng-zhua", 120);
  set_skill("lingfu-steps", 120);
  set_skill("dodge", 120);
  set_skill("force", 120);
  set_skill("yaofa", 120);
  set_skill("huntian-qigong", 120);
  set_skill("archery", 120);
  set_skill("xuanyuan-archery", 120);
  map_skill("force", "huntian-qigong");
  map_skill("unarmed", "yinfeng-zhua");
  map_skill("spells", "yaofa");
  map_skill("sword", "qixiu-jian");
  map_skill("parry", "xuanyuan-archery");
  map_skill("dodge", "lingfu-steps");
  map_skill("archery", "xuanyuan-archery");
  
  set("str", 30);
  set("per", 30);
  set("max_kee", 900);
  set("max_sen", 900);
  set("force", 3000);
  set("max_force", 1500);
  set("force_factor", 75);
  set("mana", 3000);
  set("max_mana", 1500);
  set("mana_factor", 76);
  set("inquiry", ([
                   "叛门": (: expell_me :),
                   "leave": (: expell_me :),
		   "name": "本姑娘就是这无底洞的大总管！",
		   "here": "你瞎了眼啦？这里就是鼎鼎大名的陷空山无底洞！",
		   "rumors": "不知道！找别人问去。",
		   "人肉包子": "你瞎了眼啦？本姑娘又不是厨子！",
		   	"职位": (: rank_me :),
                 ]) );  
  setup();
  carry_object("/d/obj/weapon/archery/qiankun-bow")->wield();
  carry_object("/d/obj/cloth/yuanxiang")->wear();
  carry_object("/d/obj/cloth/nichang")->wear();
  carry_object("/d/obj/weapon/archery/zhentian-arrow")->wield();
}
int rank_me()
{
        object me=this_player();
        int exp;
        exp=(int)me->query("combat_exp");
        if( me->query("title") == "陷空山无底洞掌门")
		return notify_fail("你已经是掌门人了，还来要什么职位．\n");
        if( (string)me->query("family/family_name") == "陷空山无底洞"){
                if( exp <= 100000 ){
                        me->set("title", RED"陷空山无底洞"WHT"钻地鼠精"NOR);
                  } else if(exp < 1000000 ){
                        me->set("title", RED"陷空山无底洞"WHT"人肉厨子"NOR);
                  } else if(exp < 2000000 ){
                        me->set("title", RED"陷空山无底洞"WHT"翻天鼠王"NOR);
                  } else if(exp < 3000000 ){
                        me->set("title", RED"陷空山无底洞"WHT"八臂蝠神"NOR);
                } else {
                        me->set("title", RED"陷空山无底洞"WHT"千翼蝠圣"NOR);
                }

                tell_object(me, "田鼠精对你说：你可以做"+me->query("title")+"。\n");
                tell_room(environment(me),
"田鼠精对"+me->query("name")+"说：你可以做"+me->query("title")+"。\n", ({me, me}));
         CHANNEL_D->do_channel(me,"chat","现授予本门弟子"+me->query("name")+""+me->query("title")+"一职。恭请各位仙长多加捧场！");
     me->save();  
        }
        return 1;
}
int attempt_apprentice(object me)
{
  string myname=RANK_D->query_rude(me);
  string myid=me->query("id");
  command("look "+myid);
  command("consider");
  if (me->query("combat_exp")+me->query("daoxing")>400000)
  {
    command("say "+myname+"来干什么？想来抢老娘的位子？\n");
    return 1;
  }
  if (me->query("wudidong/sell_reward")<1000)
  {
    command("say "+myname+"要想来无底洞，先提几颗人头来孝敬我！\n");
    return 1;
  }
  command("grin");
  command("say 老娘最爱吃人肉包子了。"+myname+"别忘了多给厨房弄点原料！");
  command("recruit "+myid);
  return 1;
}
int prevent_learn(object me, string skill)
{
  string myname=RANK_D->query_rude(me);

}
string expell_me(object me)
{
  me=this_player();

  if((string)me->query("family/family_name")=="陷空山无底洞")
  {
    me->set_temp("wudidong/betray", 1);
    return ("什么？想要离开？那你就别怪老娘惩罚！(jieshou)\n");
  }
  return ("你是哪里来的！滚！\n");
}
void init()
{
    add_action("do_accept", "jieshou");
}
int do_accept(string arg)
{
    object me=this_player();
    if (arg) return notify_fail("你要干什么？\n");
    if (!me->query_temp("wudidong/betray")) return notify_fail("你要接受什么？\n");
    message_vision("$N道：不错，我要离开无底洞这耗子窝！\n", me);
    me->add("betray/count", 1);
    me->add("betray/wudidong", 1);
    me->delete("family");
    me->delete("class");
    me->set("title", "普通百姓");
    me->set("combat_exp", me->query("combat_exp")*80/100);
    me->set("daoxing", me->query("daoxing")*80/100);
    if (me->query_skill("yaofa"))
    {
        me->delete_skill("yaofa");
	//me->set_skill("yaofa", me->query_skill("yaofa")/2);
	//if (me->query_skill("yaofa")>30) me->set_skill("yaofa", 30);
    }
    if (me->query_skill("huntian-qigong"))
    {
        me->delete_skill("huntian-qigong");
	//me->set_skill("huntian-qigong", me->query_skill("huntian-qigong")/2);
	//if (me->query_skill("huntian-qigong")>30) me->set_skill("huntian-qigong", 30);
    }
    me->save();
    return 1;
}
int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob))
  {
    ob->set("class", "yaomo");
  }
}
�
