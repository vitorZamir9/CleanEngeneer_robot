@echo off
@rem Altere o IP para o IP do Orange Pi
scp -r RaspNewforEv3* new@10.42.0.1:~\programacao_rasp4
@rem ssh new@10.42.0.1 "killall RaspNewforEv3.py"