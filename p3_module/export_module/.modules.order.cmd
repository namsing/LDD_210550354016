cmd_/home/pi/device-drivers/native/p3_module/export_module/modules.order := {   echo /home/pi/device-drivers/native/p3_module/export_module/add.ko;   echo /home/pi/device-drivers/native/p3_module/export_module/avg.ko; :; } | awk '!x[$$0]++' - > /home/pi/device-drivers/native/p3_module/export_module/modules.order