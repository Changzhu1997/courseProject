-- This chisel is used to get process duration information
-- Chisel description
description = "process duration chisel"
short_description = "basic"
category = "misc"
-- Chisel argument list
args = {}
-- initialization callback
function on_init()
       -- Request the fileds that we need
fdir = chisel.request_field("evt.dir")
res = chisel.request_field("evt.rawarg.res")
return true
end
-- Event parsing callback
function on_event()
 if evt.get_type() == "clone" and evt.field(fdir) == "<" then
	 if evt.field(res) == 0 then
		 return false
         end
	 chisel.set_event_formatter("clone   %evt.rawarg.res   %evt.datetime   pid:%proc.pid   %proc.name   ppid:%evt.rawarg.ptid")
         return true
 end

 if evt.get_type() == "fork" and evt.field(fdir) == "<" then
         chisel.set_event_formatter("clone   %evt.rawarg.res   %evt.datetime   pid:%proc.pid   %proc.name   ppid:%evt.rawarg.ptid")
         return true
 end

 if evt.get_type() == "vfork" and evt.field(fdir) == "<" then
         chisel.set_event_formatter("clone   %evt.rawarg.res   %evt.datetime   pid:%proc.pid   %proc.name   ppid:%evt.rawarg.ptid")
	 return true
 end


 if evt.get_type() == "kill" and evt.field(fdir) == ">" then
         chisel.set_event_formatter("kill   %evt.args   %evt.datetime   pid:%proc.pid   %proc.name   %thread.ismain")
         return true
 end
  
 if evt.get_type() == "procexit" then
         chisel.set_event_formatter("proexit   %thread.tid   %proc.name   %evt.datetime   %evt.args   %thread.ismain")
         return true
 end
       return false
end

