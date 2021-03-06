// hufa.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string expell_me(object me);

void create()
{
       set_name(HIW"护法尊者"NOR, ({"hufa zunzhe", "zunzhe"}));
       set("long", "武圣门守派尊者，门派大小事物问他都知道。\n");
       set("title", HIC"武帝门"NOR);
       set("gender", "男性");
       set("age", 1000);
       set("class", "wusheng");
       set("attitude", "friendly");
       set("shen_type", 1);
       set("rank_info/respect", "护法");
       set("looking", "英俊潇洒，玉树临风，风流倜傥。");
       set("max_kee", 1000);
       set("max_gin", 100);
       set("max_sen", 1000);
       set("force", 1000);
       set("max_force", 500);
       set("force_factor", 10);
       set("max_mana", 500);
       set("mana", 1000);
       set("mana_factor", 10);
       set("combat_exp", 1000000);
       set("daoxing", 1100000);

        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("spells", 100);  
        set_skill("feisheng", 300);
        set_skill("literate", 100);
        set_skill("sword", 100);  
        set_skill("wuying", 300);
        set_skill("fumobashi", 300);  
        set_skill("mizongbu", 100);
        set_skill("stick", 200);
        set_skill("yinglong-stick", 200);
        set_skill("dodge", 100);  
        set_skill("force", 100);   
        set_skill("xiantian", 300);

        map_skill("spells", "feisheng");
      map_skill("stick", "yinglong-stick");
        map_skill("unarmed", "fumobashi");
        map_skill("force", "xiantian");
        map_skill("sword", "wuying");
        map_skill("parry", "wuying");
        map_skill("dodge", "mizongbu");

	set("inquiry", ([
	"出门" : (: expell_me :),
	"leave" : (: expell_me :),
	]) );
	
	create_family("武圣门", 1, "护法");
	
	setup();
	carry_object("/d/obj/armor/jinjia")->wear();
}

string expell_me(object me)
{       
        me=this_player();
        if((string)me->query("family/family_name")=="武圣门") {
                message_vision("护法尊者胡子抖抖，好像非常生气。\n", me);
                me->set_temp("betray", 1);
                message_vision("护法尊者对$N嚷嚷着：小东西，你说话是真心话(true)？\n", me);
                return ("气死我了，气死我了！\n");
}
        return ("问什么问！自己想去！\n");
}
void init()
{     add_action("do_true", "true");
}

int do_true(string arg)
{

        if(this_player()->query("family/family_name") != "武圣门" )
                return 0;
        if(this_player()->query_temp("betray")) {
                message_vision("$N答道：弟子讲的真心话！\n\n", this_player());
                message_vision("护法尊者叹了口气，既是如此，你便下山吧！\n", this_player());
                this_player()->set("combat_exp", this_player()->query("combat_exp")*80/100);
		this_player()->set("daoxing", this_player()->query("daoxing")*80/100);
		if( this_player()->query_skill("feisheng") )
		    this_player()->delete_skill("feisheng");
		if( this_player()->query_skill("xiantian") )
	            this_player()->delete_skill("xiantian");
                this_player()->add("betray/count", 1);
                this_player()->add("betray/wusheng", 1);
                this_player()->delete("family");
                this_player()->delete("class");
                this_player()->set("title", "普通百姓");
                this_player()->set("faith",0);
                this_player()->set_temp("betray", 0);
                this_player()->save();
                message_vision("护法尊者伸出手将$N一推，$N化作一股青烟向东而去 ... \n", this_player());
                this_player()->move("/d/city/center");
                tell_room( environment(this_player()),"天空上噗噗嗦嗦几声响，掉下个人来！\n", ({this_player()}));
                this_player()->unconcious();            
                return 1;
                }
        return 0;
}

void attempt_apprentice(object ob)
{	ob=this_player();
	if( (string)ob->query("family/family_name")=="武圣门") {
	if ((int)ob->query("daoxing") < 1000000 ) {
  	command("say 我们降魔除妖之人最重的就是道行，" + RANK_D->query_respect(ob) + "还需多加努力才能早悟大道。\n");
	return;
	}

	if( (int)ob->query("pending/kick_out")) {
	command("say 这位" + RANK_D->query_respect(ob) + "你曾背叛孔武大帝，本护法最恨像你这样的人，我不原再收你为徒了！\n");
	command("sigh");
	return;
	}

	if ((int)ob->query_int() < 40) {
	command("say 这位" + RANK_D->query_respect(ob) + "悟性太低，恐怕收了你也难有作为！\n");
	command("sigh");
	return;
	}
    if( (int)ob->query_skill("feisheng", 1) < 150 ) {
	command("say 这位" + RANK_D->query_respect(ob) + "对我飞升大法领会还不够深，现在收你也是勉为其难，不如作罢！\n");
	command("sigh");
	return;
	}
        command("smile");
        command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
        command("recruit " + ob->query("id") );
	return;
	}
        command("shake");
        command("say 老夫不收外门弟子，" + RANK_D->query_respect(ob) + "还是另寻他人吧！\n");
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        ob->set("class", "wusheng");
}

�
