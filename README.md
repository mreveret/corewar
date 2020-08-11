# corewar

Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer. These battle programs are written in an abstract assembly language called Redcode.


VM : Machine Virtuelle
-
- L'arene est constitue de 4096 octets;
- L'arene est circulaire;
- Chaque instruction s'execute uniquement a la fin de son cycle(et attends toute sa durée);
- Les processus s'executent sequentiellement et dans le meme espace memoire, du dernier née au premier née;

Champions :
-
- Le bytecode des champions est généré grace a l'asm qui traduit l'assembleur des .s en .cor.
- Le bytecode est un ensemble d'instruction, suivis de ses parametres, qui defini donc les champions.

Processus :
-
Un processus dipose de :<br/>
- Un Live : Une valeur qui designe si le processus est vivant.
- Un PC : Registre special qui contient l'adresse dans la memoire de la VM.<br/>
- Un Carry : Un flag qui vaut 1 si l'opperation a reussie. (Si le resultat de l'operation == 0)<br/>
- 16 Registres : Chaque fait REG_SIZE (4) octets. A l'initialisation de l'arene, le Carry, le Live, et les Registres sont mis a 0, hormis le premier registre, ou est contenu le numero du joueur. A la copie d'un processus (fork, lfork), le Carry, le Live et les registres sont copié.

Regles :
-
- Quand il n'y a plus de processus en vie, la partie est finie, et le gagnant est le dernier joueur rapporté en vie (Live);
- Tous les CYCLE_TO_DIE, la machine verifie que chaque processus est vivant (Live). Si le Live est a 0, le processus est detruit. Sinon, il reste en vie et son Live est mis a 0.
- La decrementation de CYCLE_TO_DIE est de CYCLE_DELTA (-50). Elle s'effectue lorsque CYCLE_TO_DIE cycle est passé et qu'il y a eu NBR_LIVE (21) exectute par l'ensemble des processus durant le CYCLE_TO_DIE. Sinon on augmente CHECK de 1. Lorsque CHECK atteint MAX_CHECKS, la VM execute une verification des processus.;

Instructions basic
-

| Mnemonic |                               Effects                        |
|:----------:| ----------------------------------------------------------- |
| 0x01 (live)|Suivie de 4 octets qui représente le numéro du joueur. Cette instruction indique que ce joueur est en vie. (pas d’octet de codage des paramètres).                                    |
|0x02 (ld)|Cette instruction prend 2 paramètres le deuxième est forcement un registre (pas le PC). Elle load la valeur du premier paramètre dans le registre. Cette opération modifie le carry. ``ld 34,r3`` charge les `REG_SIZE` octets a partir de l’adresse `(PC + (34 % IDX_MOD))` dans le registre r3.|
|0x03 (st)|Cette instruction prend 2 paramètres. Elle store (`REG_SIZE` octets) la valeur du premier argument (toujours un registre) dans le second. `st r4,34` store la valeur de r4 a l’adresse`(PC + (34 % IDX_MOD))`, `st r3,r8` copie r3 dans r8|
|0x04 (add)|Cette instruction prend 3 registres en paramètre, additionne le contenu des 2 premiers et met le résultat dans le troisième. Cette opération modifie le carry. `add r2,r3,r5` additionne r2 et r3 et mets le résultat dans r5|
|0x05 (sub)|Même que add mais soustrait|
|0x06 (and)|p1 & p2 -> p3 le paramètre 3 et toujours un registre. Cette opération modifie le carry. `and r2,%0,r3` met r2 & 0 dans r3|
|0x07 (or)|Même que and mais avec le ou (&#124; du c).|
|0x08 (xor)|Même que and mais avec le ou exclusif (^ du c).|
|0x09 (zjmp)|Cette instruction n’est pas suivie d’octet pour décrire les paramètres. Elle prend toujours un index (`IND_SIZE`) et fait un saut a cet index si le carry est à un. Si le carry est nul, zjmp ne fait rien mais consomme le même temps. `zjmp %23` met si carry == 1 met `(PC + (23 % IDX_MOD))` dans le PC.|
|0x0A (ldi)|Cette opération modifie le carry. `ldi 3,%4,r1` lit `IND_SIZE` octets à l’adresse : `(PC + (3 % IDX_MOD))` ajoute 4 à cette valeur. On nommera S cette somme. On lit `REG_SIZE` octets a l’adresse `(PC + (S % IDX_MOD))` qu’on copie dans r1. Les paramètre 1 et 2 sont des index.|
|0x0B (sti)|`sti r2,%4,%5` sti copie `REG_SIZE` octets de r2 a l’adresse `(4 + 5)`. Les paramètres 2 et 3 sont des index. Si les paramètres 2 ou 3 sont des registres, on utilisera leur contenu comme un index.|
0x0C (fork)|Cette instruction n’est pas suivie d’octet pour décrire les paramètres. Elle prend toujours un index et crée un nouveau programme qui s’exécute a partir de l’adresse:`(PC + (premier paramètre % IDX_MOD))`<br>`fork %34` crée un nouveau programme. Le nouveau programme hérite des différents états du père.|
0x0D (lld)|Comme ld sans le `%IDX_MOD` Cette opération modifie le carry.|
0x0E (lldi)|Comme ldi sans le `%IDX_MOD` Cette opération modifie le carry.|
0x0F (lfork)|Comme fork sans le `%IDX_MOD` Cette opération modifie le carry.|
0x10 (aff)|Cette instruction est suivi d’un octet de paramétrage pour décrire les paramètres. Elle prend en paramètre un registre et affiche le caractère dont le code ascii est présent dans ce registre. (un modulo 256 est applique au code ascii, le caractère est affiché sur la sortie standard).<br>Ex :` ld %42,r3` puis `aff r3` affiche ’*’ sur la sortie standard.|
