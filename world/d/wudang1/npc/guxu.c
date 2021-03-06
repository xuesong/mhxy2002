//By tianlin@mhxy for 2001.9.30
//从新修改
inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
	set_name("谷虚道长", ({ "guxu daozhang", "guxu" }));
	set("long", 
		"他就是俞莲舟的弟子谷虚道长。\n"
		"他今年四十岁，主管武当派的俗事。\n");
	set("gender", "男性");
	set("age", 40);
	set("attitude", "peaceful");
	set("shen_type", 1);
       set("class", "wudang");
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	
	set("max_kee", 1000);
	set("max_sen", 800);
	set("force", 1000);
	set("max_force", 1000);
	set("mana", 1000);
	set("max_mana", 1000);
       set("force_factor", 90);
       set("mana_factor", 80);
	set("combat_exp", 60000);
	set("daoxing", 128000);

	set_skill("force", 60);
	set_skill("wudang-force", 40);
	set_skill("dodge", 60);
	set_skill("tiyunzong", 40);
	set_skill("unarmed", 60);
	set_skill("taiji-quan", 60);
	set_skill("parry", 60);
	set_skill("sword", 60);
	set_skill("taiji-jian", 40);
	set_skill("wudang-xianfa", 60);
	set_skill("spells", 60);
  	set_skill("literate", 80);

	map_skill("force", "wudang-force");
	map_skill("spells", "wudang-xianfa");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");

	create_family("武当派", 3, "弟子");
	set("class", "wudang");

	set("inquiry", 
		([
			"道德经" : (: ask_me :),
		]));
                                
	set("book_count", 1);

	setup();
	carry_object("/clone/weapon/changjian")->wield();
}

void attempt_apprentice(object ob)
{
        if ( ((int)ob->query("combat_exp") < 100000)) {
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应在道德及武功方面多下努力，来日方长吗！");
                return;
        }
	command("say 好吧，贫道就收下你了。");
	command("recruit " + ob->query("id"));
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "wudang");
                ob->set("title", "[1;33m武当派[1;37m第[1;31m四[1;37m代弟子[2;37;0m");
}

string ask_me()
{
        mapping fam; 
        object ob;

        if (!(fam = this_player()->query("family")) 
	    || fam["family_name"] != "武当派")
                return RANK_D->query_respect(this_player()) + 
                "与本派素无来往，不知此话从何谈起？";
        if (query("book_count") < 1)
                return "你来晚了，本派的道德真经不在此处。";
        add("book_count", -1);
        ob = new("/d/wudang1/obj/daode");
        ob->move(this_player());
        return "好吧，这本「道德经」你拿回去好好钻研。";
}
