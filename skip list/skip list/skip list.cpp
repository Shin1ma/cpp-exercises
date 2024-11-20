// skip list.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include "SkipList.h"

int main()
{
	//simply implementation

	skip_list sl;
    int inp;
	while (true) {
		try {

			std::cout << "the list is: ";
			for (int i = 1; i <= sl.size(); i++) std::cout << sl[i].val << ", ";
			std::cout << "\n";
			std::cout << "please enter: 1. to pushback, 2. to pop-in, 3. to erase, 4.to exit\n";
			std::cin >> inp;
			switch (inp)
			{
			case 1: {
				int val;
				std::cout << "enter a number: ";
				std::cin >> val;
				std::cout << "\n";
				sl.pushBack(val);
				break;
			}
			case 2: {
				int val, index;
				std::cout << "enter a position from 1 to " << sl.size() << ": ";
				std::cin >> index;
				std::cout << "\n";
				std::cout << "enter a number: ";
				std::cin >> val;
				std::cout << "\n";
				sl.popIn(val, index);
				break;
			}
			case 3: {
				int index;
				std::cout << "enter a position from 1 to " << sl.size() << ": ";
				std::cin >> index;
				std::cout << "\n";
				sl.erase(index);
				break;
			}
			case 4:
				return 0;
			default:
				std::cout << "not a valid option\n";
				break;
			}
		}
		catch (const std::runtime_error& e) {
			std::cout << e.what() << "\n\n";
		}
	}
}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
