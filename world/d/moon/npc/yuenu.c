//change.c
inherit NPC;
inherit F_MASTER;
int rank_me();
#include <ansi.h>

void create()
{
       set_name("月奴", ({"yue nu", "yuenu", "yue","master"}));
       set("long",
"她乃是桂树采天地之精华化成，后拜嫦娥为师．\n");
       set("title", "桂花仙");
       set("gender", "女性");
       set("age", 20);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "仙姑");
       set("per", 30);
	set("int", 30);
       set("max_kee", 500);
       set("max_gin", 500);
       set("max_sen", 500);
       set("force", 500);
       set("max_force", 500);
       set("force_factor", 20);
       set("max_mana", 300);
       set("mana", 300);
       set("mana_factor", 20);
       set("combat_exp", 200000);
  set("daoxing", 100000);


        set("eff_dx", 70000);
        set("nkgain", 260);

       set_skill("literate", 20);
       set_skill("unarmed", 50);
       set_skill("dodge", 80);
       set_skill("force", 50);
       set_skill("parry", 50);
       set_skill("sword", 50);
       set_skill("spells", 50);
        set_skill("moonshentong", 60);
        set_skill("baihua-zhang", 60);
        set_skill("moonforce", 60);
        set_skill("snowsword", 60);
        set_skill("moondance", 60);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("dodge", "moondance");
        set("inquiry", ([
//        "回去"    : (: kick_back :),
//        "back"  : (: kick_back :),
         "职位": (: rank_me :),
                ]) );
create_family("月宫", 3, "弟子");
setup();

        carry_object("/d/moon/obj/luoyi")->wear();
      //  carry_object("/d/moon/obj/guihuajian")->wield();
}
int rank_me()
{
        object me=this_player();
        int exp;
        exp=(int)me->query("combat_exp");
        if( me->query("title") == "广寒宫传人")
		return notify_fail("你已经是掌门人了，还来要什么职位．\n");
        if( (string)me->query("family/family_name") == "月宫"){
                if( exp <= 100000 ){
                        me->set("title", HIM"昆仑月宫"WHT"伺女"NOR);
                  } else if(exp <= 1000000 ){
                        me->set("title", HIM"昆仑月宫"WHT"惊虹舞姬"NOR);
                  } else if(exp <= 2000000 ){
                        me->set("title", HIM"昆仑月宫"WHT"飘渺舞仙"NOR);
                  } else if(exp <= 3000000 ){
                        me->set("title", HIM"昆仑月宫"WHT"逍遥圣女"NOR);
                } else {
                        me->set("title", HIM"昆仑月宫"WHT"补天圣母"NOR);
                }

                tell_object(me, "月奴对你说：你可以做"+me->query("title")+"。\n");
                tell_room(environment(me),
"月奴对"+me->query("name")+"说：你可以做"+me->query("title")+"。\n", ({me, me}));
         CHANNEL_D->do_channel(me,"chat","现授予本门弟子"+me->query("name")+""NOR+me->query("title")+HIC"一职。恭请各位仙长多加捧场！");
     me->save();  
        }
        return 1;
}
void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="女性")){
           command("shake");
           command("say 我们月宫只收女徒，这位" +
RANK_D->query_respect(ob) + "还是另请高就吧。\n");
           return;
        }

        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
"多加努力，把我们月宫发扬光大。\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
}
�
