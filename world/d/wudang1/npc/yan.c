//[4;53m[1;31mBy tianlin@mhxy for 2001.9.27[2;37;0m
//部分优化

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("俞岱岩", ({ "yu daiyan", "yu" }));
        set("nickname", HIW"武当"NOR+HIR"三侠"NOR);
        set("long",
                "他就是张三丰的最不幸的弟子、武当七侠之三的俞岱岩。\n"
                "身穿一件干干净净的青布长衫。\n"
                "他不过三十出头年纪，双腿残废，张真人命他主持真武剑阵。\n");
        set("gender", "男性");
        set("age", 31);
        set("attitude", "peaceful");
        set("class", "swordsman");
        set("shen_type", 1);
        set("str", 28);
        set("int", 30);
        set("con", 28);
        set("dex", 28);

        set("max_kee", 3000);
        set("max_sen", 3000);
        set("force", 3500);
        set("max_force", 1500);
        set("mana", 3000);
        set("max_mana", 3000);
        set("force_factor", 90);
        set("mana_factor", 70);
        set("combat_exp", 250000);
        set("daoxing", 250000);

        set_skill("force", 100);
        set_skill("wudang-force", 140);
        set_skill("spells", 170);
        set_skill("wudang-xianfa", 100);
        set_skill("dodge", 150);
        set_skill("tiyunzong", 150);
        set_skill("unarmed", 100);
        set_skill("taiji-quan", 100);
        set_skill("parry", 110);
        set_skill("sword", 120);

        map_skill("force", "wudang-force");
        map_skill("spells", "wudang-xianfa");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
	set("chat_chance", 1);

        set("chat_msg", ({
            "俞岱岩说道：真武剑阵是恩师的心血。",
            "俞岱岩仰天叹道：哪位巫师能治好我的腿，我也请鸭庄一顿。"
        }));

        create_family("武当派", 2, "弟子");

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang1/obj/bluecloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting",2 , ob);
        }
}

void greeting(object ob)
{
   int i;
   if (((int)ob->query_skill("wudang-force", 1) == 0))
   {
      message_vision(CYN"十三弟子对$N齐声喝道：你这个邪魔外道，敢来真武剑阵？\n\n"NOR,ob);
      ob->set("kee",30);
      if ((int)ob->query("combat_exp") <2000) ob->set("combat_exp",1);
         else ob->add("combat_exp",-1000);
      message_vision(CYN"真武剑阵顿时启动，高台上剑气纵横，把$N围在中央。\n"NOR,ob);
      message_vision(CYN"十三口长剑齐出，在$N身上划出了十三道口子，鲜血淋漓。\n"NOR,ob);
      say(CYN"\n\n俞岱岩脸现怒容：“邪魔外道，也敢闯真武剑阵！”\n");
      message_vision("俞岱岩居高临下，起手一掌把$N劈落高台。\n\n\n"NOR,ob);
      ob->move("/d/wudang1/nanyangong");
      CHANNEL_D->do_channel(this_object(),"chat",sprintf("%s 私闯真武剑阵，念其成长不易，暂免一死！",ob->name(1)));
   }
}

void attempt_apprentice(object me)
{
       if ( ((int)me->query("combat_exp") < 100000)) {
         command("say " + RANK_D->query_respect(me) +
                        "是否还应在道德及武功方面多下努力，来日方长吗！");
                return;
        }
        if ((int)me->query_skill("wudang-force", 1) < 30) {
                command("say 我武当派乃内家武功，最重视内功心法。");
                command("say " + RANK_D->query_respect(me) +
                        "是否还应该在太极神功上多下点功夫？");
                return;
        }
        command("say 好吧，我就收下你了。");
        command("recruit " + me->query("id"));
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "wudang");
                ob->set("title", "[1;33m武当派[1;37m第[1;36m三[1;37m代弟子[2;37;0m");
}
