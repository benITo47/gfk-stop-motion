# Dokumentacja

## Autorzy
_Daniel Czapla, Bartłomiej Obrochta, Franciszek Urbański_

## Opis projektu

## Założenia wstępne

## Analiza projektu

### Dane wejściowe

### Dane wyjściowe

### Struktury danych

### GUI

### Zadania
Zob. [Podział pracy i analiza czasowa](#podział-pracy-i-analiza-czasowa)

### Narzędzia programistyczne

## Podział pracy i analiza czasowa
We wstępnej analizie projektu wyodrębniliśmy następujące trzy zadania, i wstępnie podzielilismy się odpowiedzialnością za nie:
- **Zaprojektowanie i utworzenie GUI**; odpowiedzialny: _Daniel Czapla_,
- **Opracowanie logiki rysowania (wyświetlania oraz tworzenia) animacji w GUI**; odpowiedzialny: _Bartłomiej Obrochta_,
- **Opracowanie formatu zapisywanego pliku oraz algorytmu jego zapisu**; odpowiedzialny: _Franciszek Urbański_.
W praktyce oczywiście było wiele przestrzeni wspólnej między tymi ogólnymi zadaniami, przez co też granice odpowiedzialności rozmywały się. Nad niektórymi funkcjonalnościami, w szczególności związanymi z kompatybilnością z różnymi systemami operacyjnymi, siedzieliśmy również wspólnie.

### GUI
- Projekt - x h
- Implementacja - x h
- Poprawki w miarę powstawania nowych funkcjonalności - x h
- Zapewnienie kompatybilności z różnymi rodzajami wyświetlaczy i systemów operacyjnych - 3h

### Rysowanie
- Podstawowa funkcjonalność rysowania na panelu - x h
- Podstawowe wyświetlanie kształtów i tła - x h
- Zapewnienie kompatybilności z systemem zapisu plików - x h
- Implementacja warstwy środkowej i jej kontroli przeźroczystości - x h
- Rozwinięcie funkcjonalności rysowania z dynamicznie wyświetlanymi kształtami - x h
- Zapewnienie kompatybilności z systemem MS Windows - 3 h

### Zapis do pliku
- Opracowanie formatu zapisu pliku, wraz z formatem zapisu parametrów - 1h
- Opracowanie i próby implementacji struktury wewnętrznej zapisu animacji (`Parser.h`) - 4h
- Zapewnienie kompatybilności z logiką rysowania - 2h
- Implementacja funkcji zapisu kształtu, klatki - 1h
- Implementacja kopiowania obrazów - 1h
- Poprawianie pojawiających się błędów związanych z edge-case'ami oraz kompatybilnością z MacOS - 1h

## Opis najważniejszych algorytmów
### Rysowanie

### Zapis do pliku
Algorytm zapisu do pliku oraz format pliku opisane są w opisie szczegółowym pliku `Parser.h`.

## Kodowanie
Korzystaliśmy z systemu kontroli wersji `git`.

## Testowanie
Testowanie przeprowadzaliśmy w następnych etapach:
- na bieżąco, podczas pisania kodu - np. podgląd GUI, test zapisu przez zapisanie i wczytanie każdego kształtu przed narysowaniem. Każdą funkcjonalność przed spushowaniem do repozytorium staraliśmy się w miarę możliwości przetestować;
- code review na pull request'ach - przy wprowadzaniu bardziej zaawansowanych zmian, prosiliśmy się nawzajem o sprawdzenie i przetestowanie kodu. Dodatkową tego korzyścią było to, że sprawdzaliśmy czy program działa na różnych systemach operacyjnych;
- test integracyjny: stworzenie projektu przykładowego, korzystającego ze wszystkich funkcjonalności programu

Podczas sprawdzania poprawności kodu, próbowaliśmy zawsze rozważyć wszystkie edge case'y w których program mógłby zawieść. Znaleźliśmy w ten sposób (a następnie poprawiliśmy) wiele bug'ów, m.in.:
- nieprawidłowa obsługa wydarzeń przy anulowaniu wyjścia z programu,
- błąd przy wczytywaniu animacji bez tła,
- niepoprawne wczytywanie animacji po zmianie sposobu rysowania.

## Wnioski