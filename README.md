# Progetto Netflix
## Traccia
Realizzare un sistema per la visualizzazione di serie tv e film tipo *Netflix*.
Nello specifico, realizzare le classi **Database**, **Film** e Serie.
La classe **Database** è caratterizzata da una lista di film e una di serie tv.
Al database si possono aggiungere e rimuovere film e serie tv.

Inoltre, si possono:
* Visualizzare il film e la serie più apprezzati al momento;
* Richiedere un film (o una serie) simile ad un film (o una serie) dato.
Scegliere liberamente come interpretare il concetto di contenuto "simile".

La classe **Film** è caratterizzata da un *titolo*, un *genere* e una *durata* mentre la classe **Serie** è caratterizzata da un *titolo*, un *genere* e un *numero di stagioni*.

Realizzare inoltre le classi **Account** e **Profilo**.
La classe **Account** è caratterizzata da *email*, *password* e una lista dei profili associabili a quell’account.
Alla classe **Account** si possono aggiungere nuovi profili fino a un massimo di 4.
La classe **Profilo**, invece, è caratterizzata dal *nome*, una lista di film visti e una lista di serie viste.
La classe **Profilo** offre funzionalità per vedere un film o una serie.
Se si cerca di vedere un contenuto già visto, il sistema mostra un opportuno messaggio per avvisare l’utente.
Dopo aver terminato la visione del contenuto, all’utente è richiesto un feedback sul gradimento (voto da 1 a 5).
Strutturare opportunamente le 5 classi indicate, individuando gli attributi e i metodi necessari a realizzare tutte le funzionalità richieste.

### Suggerimento:
Sottolineate i sostantivi chiave per individuare gli attributi e i verbi per i metodi
Creare un database con 10 film e 10 serie tv.

All’avvio dell’applicativo, deve essere possibile scegliere tra la creazione di un nuovo account (con i relativi 4 profili) o il login, in caso di account già registrato.
Decidere arbitrariamente se prendere le informazioni necessarie alla creazione degli oggetti in maniera statica, da input o da file.
Testare le funzionalità implementate facendo vedere film e serie ai vari profili e verificando l’aggiornamento dei contenuti più graditi.

## Istruzioni finali
Il progetto deve essere svolto individualmente e in linguaggio **C++**.
Inoltre Bisogna realizzare un report, di massimo 6 pagine, che deve contenere una spiegazione di come avete interpretato la traccia e come avete pensato di impostare la vostra soluzione, anche mediante l’aggiunta di *Class Diagram* che mostrino graficamente le classi individuate per la soluzione.
Esso costituisce un manuale utente e una guida all’uso del vostro programma.