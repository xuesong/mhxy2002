//by ephq

#include <ansi.h>
#include <dianxue.h>
inherit SSERVER;
void remove_xue(object tar);
int perform(object me, object target)
{
	string attack_skill,msg;
	int extra, dif, ap, dp, ap1, dp1, pp, app,dpp,t,power;
	object weapon;
	mapping data;

	extra = me->query_skill("dianxue",1) ;

	if ( extra < 100) return notify_fail("你的[点穴]还不够纯熟，还认不准哑穴！\n");


	if( !target ) target = offensive_target(me);
	if( !target
	||!target->is_character() )
// 	|| target->is_fighting(me))
		return notify_fail("你要点谁的穴。\n");

        if( target->query("channel/chat_block")>time()
        || target->query("channel/tell_block")>time() )
		return notify_fail(target->name()+"已经是哑巴了？\n");

        if((int)me->query("force") < 150 ) return notify_fail("你的内力不足！\n");
     	if(!valid_perform(me,target)) return 0;
               me->add("force", -100);

        me->receive_damage("sen", 50);

//        arg=xue[random(sizeof(xue))];


	data=type(me);
	if( data["type"]=="none" )
	return notify_fail("你所用的兵器不适合点穴。\n");

	dif=data["dif"]	;

       msg=HIC+"$N屏息凝神，";
       if( dif!=110 ) msg+="内力灌注"+me->query_temp("weapon")->name()+HIC+",";
       msg+="全神贯注的盯住$n的哑穴，\n"+NOR+MAG+"突然，";
       if( dif!=110 ) msg+="手中"+me->query_temp("weapon")->name()+"的";
       msg+=data["action"]+"$n的哑穴"+data["type"]+"去。\n\n"+NOR;

       message_vision(msg,me,target);

       ap=me->query("combat_exp");
       dp=target->query("combat_exp");
       ap1=me->query_skill("force");
       dp1=target->query_skill("force");
       pp=target->query_skill("dodge")+target->query_skill("parry");

       app=ap1*2+extra*40;
       dpp=dp1*2+pp*10;
       if( ((random(app+dpp)*dif/100 > dpp)) ||( ( random(ap+dp)>dp ) ) )
       {
       	msg=WHT+"结果，$n的哑穴被一下子"+data["type"]+"中了，顿时表情僵硬，说不出话来。\n"+NOR;
        target->set("channel/tell_block",time()+180);
        target->set("channel/chat_block",time()+180);
        target->set_temp("dianxue/xue3","哑穴");
       target->set_temp("xue3/name",me->name());
       power=extra+me->query("force_factor")*10+ap1;
       target->set_temp("xue3/power",power);
       target->start_call_out( (: call_other, __FILE__, "remove_xue", target :), 179);
       message_vision(msg,me,target);
       }
       else {
       	msg=HIY+"但是，$n似乎早就算出你会出此一招，从容的躲开了。\n"+NOR;
       message_vision(msg,me,target);
       	me->start_busy(2);
//        COMBAT_D->do_attack(target,me, target->query_temp("weapon"));
       	}

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else
target->kill_ob(me);
                }
                me->fight_ob(target);
        }
	return 1;
}

void remove_xue(object tar)
{
        if(!tar) return;
        if( !tar->query_temp("dianxue/xue3") ) return;
        tell_object(tar, "你的"+HBWHT+HIR+"哑穴"+NOR+"终于自行解开了。\n");
        tar->delete("channel/tell_block");
        tar->delete("channel/chat_block");
        tar->delete_temp("dianxue/xue3");
       return;
}