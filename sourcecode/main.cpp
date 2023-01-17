#include <iostream>
#include <stdlib.h>
#include "Manage.h"
#define clear /** / "CLS" /* DOS/WINDOWS */ "clear" /* Unix-like*/
using namespace std;

Manage admin = Manage();
Archive mediaDB = Archive();
string profilename = "";

int main() {
	int c = -1;
	do {
		system(clear);
		int j = 0;
		// se dopo un login ho superato il numero massimo di tentativi
		if(admin.isOverAttempts()) {
			cout << "\n>>>>> SUPERATO IL NUMERO MASSIMO DI TENTATIVI <<<<\n";
			return 0;
		}
		// se non sono loggato e non ho superato il numero massimo di tentativi
		else if(!admin.isSigned()) {
			cout << "*** HOME ***\n";
			// stampa dei profili del account già registrati
			cout << ++j << ". accounts-list :: lista account\n";
			if(c == j) {
				cout
					<< "**** Accounts-List!! ****"
					<< admin.getAccountsList()
					<< "\n*************************\n";
			}
			// registrazione nuovo account
			cout << ++j << ". sing-up :: registrazione\n";
			if(c == j) {
				string email, password;
				cout
					<< "**** REGISTRAZIONE!! ****\n"
					<< "email >:_ ";
				cin >> email;
				cout << "password >:_ ";
				cin >> password;
				// verifico se la registrazione funziona
				if(admin.signup(email,password)) {
					cout << ">>> REGISTRAZIONE EFFETTUATA <<<\n";
				} else {
					cout << "!!! EMAIL GIA' REGISTRATA !!!!\n";
				}
			}
			cout << ++j << ". sing-in :: effettua log-in\n";
			if(c == j) {
				string email, password;
				cout
					<< "**** LOGIN!! ****\n"
					<< "email >:_ ";
				cin >> email;
				cout << "password >:_ ";
				cin >> password;
				// verifico se il login va a buon fine
				if(admin.signin(email,password)) {
					cout
						<< ">>> LOGGATO <<<\n"
						<< "(update menu)\n";
				} else {
					cout << "!!! USERNAME o PASSWORD ERRATA !!!!\n";
				}
			}
		}
		// loggato ma non ho selezionato un profilo
		else if(
			admin.isSigned() &&
			!admin.getAccount().existsProfileName(profilename)
		) {
			profilename = "";
			cout << ">>> " << admin.getAccount().getEmail() << " <<<\n";
			// lista dei profili del utente
			cout << ++j << ". profiles-list :: lista dei profili\n";
			if(c == j) {
				cout
					<< "**** Profiles-List!! ****\n"
					<< admin.getAccount().printMyProfiles()
					<< "************************\n";
			}
			// seleziona il nome di un profilo
			cout << ++j << ". select-profile :: seleziona profilo\n";
			if(c == j) {
				cout
					<< "**** Profiles-Selection!! ****\n"
					<< "profile >:_ ";
				cin >> profilename;
				// verifico l'esistenza del profilo
				if(admin.getAccount().existsProfileName(profilename)) {
					cout
						<< "selezionato [" << profilename << "]"
						<< "\n(update menu)\n";
				} else {
					cout << "!! il profilo [" << profilename << "] NON ESISTE !!\n";
					profilename = "";
				}
			}
			// aggiunge un nuovo profilo al account corrente
			cout << ++j << ". add-profile :: aggiungi profilo\n";
			if(c == j) {
				cout
					<< "**** Profile-Adding!! ****\n"
					<< "profile >:_ ";
				cin >> profilename;
				// controllo che non esista un altro profilo con stesso nome
				if(admin.getAccount().add(profilename)) {
					cout << profilename << " added!\n";
				} else {
					cout
						<< "Error:\n"
						<< "Maybe " << profilename << " is just added!\n"
						<< "or you've many profiles!!\n";
				}
				profilename = "";
			}
			// log-out utente
			cout << ++j << ". sign-out :: log-out esci da account\n";
			if(c == j) {
				admin.signout();
				cout << "!!! LOG-OUT EFFETTUATO !!!\n(update menu)\n";
			}
		}
		// loggato con profilo selezionato
		else {
			cout
				<< ">>> " << admin.getAccount().getEmail() << "["
				<< admin.getAccount().getProfileByName(profilename).getName()
				<< "] <<<\n";
			// visualizza il catalogo dei media in elenco
			cout << ++j << ". media-list :: visualizza media in elenco\n";
			if(c == j) {
				cout << mediaDB.str();
			}
			// cerca tutti i media con criterio di similitudine
			cout << ++j << ". find-media :: cerca media in elenco\n";
			if(c == j) {
				string media = "";
				cout
					<< "**** media-Finding!! ****\n"
					<< "seek >:_ ";
				cin >> media;
				cout << mediaDB.findSameMedia(media);
			}
			// lista dei media già visti e recensiti
			cout << ++j << ". feedbacklist :: feedback lasciati\n";
			if(c == j) {
				// stampo l'elenco solo se ci sono film visti e recensiti
				if(admin.getAccount().getProfileByName(profilename).infoFeedBackMovie().length() > 0) {
					cout
						<< "****** MOVIES' Feedbacks ********\n"
						<< "STARS\tID\tType\tMIN\tGENRE\tTITLE\n"
						<< admin.getAccount().getProfileByName(profilename).infoFeedBackMovie();
				}
				// stampo l'elenco solo se ci sono serie viste e recensiti
				if(admin.getAccount().getProfileByName(profilename).infoFeedBackSerie().length() > 0) {
					cout
						<< "****** SERIES' Feedbacks ********\n"
						<< "STARS\tID\tType\tMIN\tGENRE\tTITLE\n"
						<< admin.getAccount().getProfileByName(profilename).infoFeedBackSerie();
				}
			}
			// lascio recensioni ai media
			cout << ++j << ". watch & give feedback :: guarda media e lascia feedback\n";
			if(c == j) {
				char type = ' ';
				int
					idmedia = 0,
					stars = 0;
				cout << "*** give feedback ***\n";
				cout << "(type [M]ovie or [S]erie) >:_ ";
				cin >> type;
				// chiedo se recensire un film o una serie
				if (type == 'M' || type == 'm') {
					cout << "(id movie) >:_ ";
					cin >> idmedia;
					// controllo esistenza del id nel catalogo
					if(mediaDB.getMovieById(idmedia).getId() > 0) {
						// se trovo il media dal ID stampo le info
						cout
							<< "you've select:\n"
							<< mediaDB.getMovieById(idmedia).str();
						cout << "(num stars) >:_ ";
						cin >> stars;
						// controllo se posso lasciare un feedback se non è già recensito
						if(admin.getAccount().getProfileByName(profilename).setFeedBackToMovie(idmedia, stars)) {
							cout << "!!! FEEDBACK OK !!!\n";
						} else {
							cout << "!!! Maybe you have just give feedbak for this media !!!\n";
						}
					} else {
						cout << "NOT FIND THAT MOVIE\n";
					}
				} else if (type == 'S' || type == 's') {
					cout << "(id serie) >:_ ";
					cin >> idmedia;
					if(mediaDB.getMovieById(idmedia).getId() > 0) {
						cout
							<< "you've select:\n"
							<< mediaDB.getSerieById(idmedia).str();
						cout << "(num stars) >:_ ";
						cin >> stars;
						if(admin.getAccount().getProfileByName(profilename).setFeedBackToSerie(idmedia, stars)) {
							cout << "!!! FEEDBACK OK !!!\n";
						} else {
							cout << "!!! Maybe you have just give feedbak for this media !!!\n";
						}
					} else {
						cout << "NOT FIND THAT MOVIE\n";
					}
				}
			}
			// esci dal profilo selezionato
			cout << ++j << ". leave-profile :: deseleziona il profilo\n";
			if(c == j) {
				profilename = "";
				cout << "(update menu)\n";
			}
		}
		cout
			<< "\n9. (update menu :: aggiorna menu)"
			<< "\n0. EXIT\n\n>:_ ";
		cin >> c;
	} while (c != 0);
	system(clear);
	cout << "see you soon...\n";
	return 0;
}