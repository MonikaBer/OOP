# Opis

Program zarządza zbiorem obrazków (traktowanych jako zbiór pixeli białych i czarnych). Udostępnia następujące operacje na obrazkach:
- wyświetlenie danego obrazka
- odczyt danego pixela (czy jest biały, czy czarny)
- zmiana koloru pixela
- suma logiczna dwóch obrazków
- iloczyn logiczny dwóch obrazków
- odbicie lustrzane obrazka


KONWENCJA

Każdy obiekt klasy Picture jest obrazkiem będącym zbiorem  pixeli białych. Obrazek ma wymiar pionowy (liczbe wierszy pixeli) i poziomy (liczbe kolumn pixeli). Ten zbiór pixeli jest przechowywany w zmiennej strukturze danych zwany mapą, która pozwala na wydajne alokowanie pamięci dla pixeli w pamięci oraz szybkie wyszukiwanie danego pixela (czy on występuje czy nie w mapie). Każdy element mapy ma postać <klucz, wartość>, co odpowiada danemu wierszowi obrazka. Kluczem jest nr wiersza (numeracja od 0 do h-1), a wartością jest uporządkowany zbiór pozycji pixeli w wierszu, czyli numery kolumn (od 0 do v-1). Ten zbiór pozycji w wierszu z kolei został zaimplementowany w strukturze set, która jest uporządkowanym zbiorem i jest implementacją drzewa czerwono-czarnego, w którym średni czas przeszukiwania jest szybszy w porównaniu ze standardowymi strukturami danych typu np. wektor.

Tworzenie plików binarnych:
1) Polecenie 'make' tworzy plik binarny dla pixels (programu głównego) i od razu go uruchamia. W celu ponownego uruchomienia należy wpisać komendę './main ./resources', gdzie './resources' to ścieżka do katalogu z przykładowymi obrazkami. Jeśli ta komenda nie działa to należy jeszcze raz wywołać polecenie 'make' (widocznie wcześniej program zakończył się z kodem różnym od 0 i plik binarny został usunięty).

2) Polecenie 'make tests' tworzy plik binarny z testami i od razu go uruchamia. W celu ponownego uruchomienia należy wpisać komendę './tests'.
3) W celu usunięcia plików binarnych wystarczy wpisać polecenie 'make clean'.
