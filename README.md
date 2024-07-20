Grand merci a Laura (https://github.com/lbarry9/42/), Kilian et Mathieu qui m'ont beaucoup aide sur ce projet !

Un code ici public de Philosophers, il n'est pas specialement bon ou original, mais si ca peut donner des idees ou des pistes... Meme s'il passe les testeurs (sur un PC performant hein !), je suis sur qu'il reste plein d'erreurs, n'hesitez pas a me les remonter, j'oublie toujours des trucs, et c'est un projet sur lequel j'ai bien rame. De plus, il me reste encore beaucoup de choses a saisir sur les threads, mutex et autres subtilites semaphoriques. Idem pour l'optimisation, je n'ai fait que le strict minimum. 

Pour le mandatory, strategie classique, un philo par thread (le sujet l'impose), et un monitoring depuis le main. J'ai la pretention de penser qu'il n'y a pas dix milles solutions pour repondre aux contraintes de sujet (cependant j'ai entendu parler de l'algo du banquier, c'est vrai que j'avais lu cet algo sur wiki mais sans pousser plus loin). En gros c'est les threads qui font (presque) ce qu'ils veulent, et les mutex qui permettent de reguler le flux des requetes de fourchettes et le flux des prints.

Pour le bonus, un philo par child (le sujet l'inpose), et horreur, un thread par child pour le monitoring de ce child. Oui c'est tres lourd, vous trouverez mieux facilement, mais je pense que, au moment du kill, ca permet d'etre "un peu moins mechant', a vos dissertions, mais sans moi. Un vrai plus dans ce bonus, la notion de semaphore, un outil qui permet en particulier un partage d'une donnee entre le parent et l'enfant, mais les outils autorises sont tres limites, un sem_getvalue, ou un sem_trywait, aurait peut-etre permis d'aller au-dela des concepts.

Ce projet m'a bien pris un mois et demi quand certains le font en deux semaines en attendant leur mate de minishell... en code aussi, il y a les Pogacar, et les autres qui sentent le souffle de la voiture balai dans leur dos, good thread!


Ressources :

Toutes les videos CodeVault

https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/

https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2

Un tres bon testeur pour reflechir et accompagner son travail : https://github.com/Rz-Rz/thales_tester
