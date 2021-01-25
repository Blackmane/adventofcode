# AOC2020 - Cosa ho imparato

In questo AoC2020 ho tenuto una sorta di diario di cosa ho imparato o delle piccole cose che mi sono balzate all'occhio.


## TL;DR

Credo di aver imparato molto e mi sento di essere migliorato.
La mia conoscenza del C++, come speravo, è cresciuta (ma questo grazie anche allo studio personale che ho portato avanti in parallelo).
In particolare è migliorato l'uso delle diverse strutture.

Mi sono saltati all'occhio tanti piccoli dettagli, che magari non fai caso normalmente ma che sono utili nel lavoro di tutti i giorni.


## Approccio

Ho deciso di approcciare l'AoC utilizzando esclusivamente C++. 
L'intenzione è stata quella di migliorare, per quanto possibile, la conoscenza del linguaggio. 
In particolare l'ho vista come una occasione di allenamento sugli algoritmi.

Inoltre mi sono imposto di sviluppare un codice pulito e documentato, da poter caricare su github.
Inizialmente avevo previsto anche di sfruttare CLANG TIDY, ma dopo qualche giorno ho smesso.


## Day 1 - 1 dicembre

Primo giorno e non sapevo ancora nulla della filosofia di questa competizione, per tanto ho fatto una soluzione alquanto over ingegnerizzata e complessa.

Soluzione che non pare permettere di guadagnare in efficienza. Questa soluzione esegue in 1-2 millisecondi, al contrario una soluzione più brute force ci impiega 14 millisecondi nella versione non ottimizzata e 2 millisecondi della versione ottimizzata.
Sono comunque soluzioni applicate ad un input tutto sommato piccolo, potrebbe essere interessante calcolarne la complessità computazionale al caso peggiore.


## Day 3 - 3 dicembre

Fino a questo giorno non avevo ancora capito che fosse una competizione. Per me era più un risolvere un problema tutti assieme, confrontare le soluzioni e discuterci sopra.

La situazione è un po' cambiata quando ho scoperto la leaderboard.
Ma soprattutto quando scopro i tempi con cui i migliori hanno risolto i vari problemi.

Sono stupito.

Pochi minuti per risolvere un problema che a me ha richiesto molti più minuti se non ore.


## Day 4 - 4 dicembre

Il parsing dei dati diventa un problema costante che occupa gran parte del tempo.
Ad oggi non ho ancora trovato una soluzione elegante.


## Day 5 - 5 dicembre

Dati i problemi del giorno precedente mi viene in mente di cambiare approccio, per passarne ad uno più funzionale, che mi permetta di ragionare meglio sulla risoluzione dei problemi.

Credo sia stata una buona idea, tant'è che ho usato il solito approccio in molti altri problemi.


## Day 10 - 10 dicembre

Scopro che le soluzioni da sviluppare possono anche non coprire tutti i casi possibili, ma basta che risolvano lo specifico input, che spesso ha vincoli nascosti che aiutano.

Approfondisco il mondo dell'AOC. Leggo reddit, blog, guide e consigli.


Qualche utile risorsa:

* [How to Leaderboard](https://blog.vero.site/post/advent-leaderboard)
* [A collection of awesome resources](https://github.com/Bogdanp/awesome-advent-of-code)
* [mcpower tips](https://gist.github.com/mcpower/87427528b9ba5cac6f0c679370789661)
* [Going fast](https://kevinyap.ca/2019/12/going-fast-in-advent-of-code/)

Decido di iniziare ad tenere degli appunti giornalieri, da cui nasce questo diario.


## Day 11 - 11 dicembre

Viene chiesto di manipolare una matrice 100x100.
È quindi fondamentale conoscere le caratteristiche del linguaggio, come il passaggio di parametri per riferimento.
Questo perché chiaramente copiare inutilmente le strutture è un costo non sostenibile.

Le prime esecuzioni, che prevedevano la copia delle strutture ci impiegavano circa 24 secondi.
L'uso del passaggio di riferimento ha fatto crollare il tempo di esecuzione a soli 400 millisecondi. Per scendere ulteriormente a 90 millisecondi utilizzando le ottimizzazioni.


## Day 11 bis

Inizio a riflettere sull'utilità di avere una propria libreria di utils, che implementi in tutto o in parte gli algoritmi e le strutture più utili.
Di avere uno script che permetta di generare una nuova cartella in base al giorno, con già il cmakefile e il main pronti, magari il tutto integrato con uno script che scarichi il problema e l'input del giorno.
Ulteriormente utile uno script per la compilazione e l'esecuzione e uno per la submission delle risposte.

Idee utili se si vuole risparmiare tempo e fondamentali se si vuole essere davvero competitivi.


## Day 15 - 15 dicembre

Alcuni problemi si risolvono solo a forza bruta, eseguendo quindi i vari passi.
Non esistono formule per rendere immediata la soluzione. 
Di conseguenza eseguire la risoluzione ha un costo non facilmente ammortizzabile.


## Day 16 - 16 dicembre

Mi ritrovo troppo stanco per affrontare il problema, e il parsing mi pare in quel momento una follia da gestire.

Riconosco l'importanza di fermarsi e riflettere, scrivendo prima su carta l'idea della soluzione e solo dopo iniziare ad implementarla.
Ragionare mi ha portato a scrivere codice funzionante sin da subito, al contrario le parti di codice su cui non ho ragionato mi hanno creato solo confusione e problemi.


## Day 21 - 21 dicembre

Sono costretto ad interrompere.


## Day 22 - 10 gennaio

La prima parte ci mette 1 millisecondo, mentre la seconda un minuto e mezzo.
Mi viene in mente un articolo sull'ottimizzazione del compilatore. Abilito quindi il flag -o2 e l'esecuzione della seconda parte ci impiega solo 260 millisecondi.

Il compilatore è bravissimo ad ottimizzare il codice. Per esempio con -o2 applicato al day17 si passa dai 2 secondi agli 80 millisecondi.

Dove nei giorni precedenti si fa riferimento ai tempi dati dall'ottimizzazione, i risultati sono ottenuti a posteri.


## Background

Infine una briciola di background personale.

Sono un developer e attualmente lavoro in C e C++ su ambiente linux. 

L'unica competizione che avevo mai fatto è stato il Google Hashcode del 2018, tra l'altro raggiungendo un risultato comunque decente.
Avevo già conosciuto, ma in ritardo, l'Advent of code grazie all'edizione del 2019. Non avevo approfondito molto in realtà, tant'è che avevo fatto giusto qualche giornata iniziale ad evento cominciato.

