# Dokumentacja

## 1. Tytuł projektu oraz autorzy projektu

**Tytuł projektu:** ANIMACJE POKLATKOWE

**Autorzy projektu:** 
- Daniel Czapla
- Bartłomiej Obrochta
- Franciszek Urbański

## 2. Opis projektu
**Opis projektu:**

Celem projektu jest stworzenie programu umożliwiającego tworzenie animacji w technice stop-motion. Program pozwala użytkownikowi na rysowanie wybranych kształtów dostępnych na panelu oraz na wybieranie kolorów obramowania i wypełnienia tych kształtów. Użytkownik ma możliwość dodawania dowolnej liczby kształtów do panelu, usuwania ostatniego dodanego kształtu oraz wszystkich dodanych kształtów.

Ponadto, użytkownik może dodawać nowe klatki i je usuwać. Przy dodawaniu klatki istnieje opcja wyboru, czy nowa klatka ma zawierać wszystkie kształty znajdujące się na poprzedniej klatce oraz stare tło. Użytkownik może również zmieniać przezroczystość ostatniej klatki oraz przezroczystość tła po jego wczytaniu.

Aby ułatwić użytkowanie, program wyposażony jest w menubar, który umożliwia sprawdzenie podstawowych informacji o projekcie oraz zapisanie i wczytanie stworzonej animacji. Po dodaniu określonej liczby klatek użytkownik widzi, na której obecnie klatce się znajduje. Może odtworzyć animację, zatrzymać ją oraz poruszać się między klatkami w lewo i w prawo. Dodatkowo, użytkownik ma możliwość ustawienia prędkości animacji.

## 3. Założenia wstępne przyjęte w realizacji projektu

- **Technologie i narzędzia:**
  - Język programowania: C++
  - Biblioteki graficzne: wxWidgets

- **Środowisko pracy:**
  - Uzależnione od developerów, projekt będzie rozwijany i testowany zarówno na systemach Windows, jak i macOS

- **Ograniczenia projektowe:**
  - Każda klatka tworzonych animacji musi być grafiką wektorową. Zapis każdej klatki sprowadza się do zapisania w pliku 
    informacji o podstawowych obiektach graficznych. Plik ten musi mieć postać możliwie zwartą.

- **Interfejs użytkownika:**
  - Intuicyjny panel rysowania z możliwością wyboru i edycji kształtów
  - Menubar z opcjami zapisu, wczytania, oraz podstawowymi informacjami o projekcie
  - Możliwość odtwarzania animacji złożonej ze stworzonych klatek lub wczytanej przez użytkownika
  - Wskaźnik bieżącej klatki oraz narzędzia do nawigacji między klatkami

- **Wymagania podstawowe:**
  - Program pozwala na wczytanie pierwszego pliku animacji
  - Posiada przycisk umożliwiający przejście do kolejnej klatki
  - Pozwala na zmianę jasności tła w trakcie pracy
  - Pozwala na rysowanie na klatce linii łamanych, krzywych, okręgów, elips, kwadratów i trójkątów o zadanym kolorze, z 
    wypełnieniem lub bez

- **Wymagania rozszerzone:**
  - Umożliwia ustalenie osobno koloru linii i wypełniania dla figur zamkniętych
  - Umożliwia cofnięcie ostatnio wykonanego rysowania
  - Widok posiada dodatkową warstwę pomiędzy tłem a warstwą właściwą - na warstwie tej widać klatkę narysowaną ostatnio     
    (możliwa jest zmiana poziomu przeźroczystości tej warstwy)
  - Program może być wyposażony w moduł (może być to odrębny program) pozwalający odtworzyć animację z zadaną prędkością

W projekcie zdecydowaliśmy się na implementację rozszerzonej wersji programu, aby zapewnić większą funkcjonalność i elastyczność użytkownikom.

## 4. Analiza projektu

### Dane wejściowe

### Dane wyjściowe

### Struktury danych

### Specyfikacja Interfejsu Użytkownika
Interfejs aplikacji składa się z głównego okna oraz panelu narzędziowego, który zawiera przyciski, suwaki i kontrolki do manipulacji klatkami, kształtami oraz ustawieniami animacji.

#### Główne okno

Główne okno aplikacji zawiera dwa główne elementy:

1. **Panel rysunkowy (_MyPanel_)**
   - Jest to główny obszar, na którym wyświetlane są animacje oraz dodawane kształty.
   - Użytkownik może dodawać kształty na tym panelu poprzez interakcję z myszą.

2. **Panel narzędziowy**
   - Zawiera przyciski, suwaki oraz kontrolki umożliwiające użytkownikowi interakcję z aplikacją.

#### Panel narzędziowy

Panel narzędziowy zawiera następujące elementy:

- **Przyciski operacyjne**:
  - **Add frame**: Dodaje nową klatkę do animacji.
  - **Delete frame**: Usuwa bieżącą klatkę z animacji.
  - **Delete last shape**: Usuwa ostatni dodany kształt.
  - **Delete all shapes**: Usuwa wszystkie kształty na panelu.
  - **Load background**: Ładuje obraz tła z pliku.

- **Przyciski sterujące animacją**:
  - **Previous frame (_<-_)**: Przechodzi do poprzedniej klatki animacji.
  - **Play/Stop (_>_ / _x_)**: Odtwarza lub zatrzymuje animację.
  - **Next frame (_->_)**: Przechodzi do następnej klatki animacji.

  - **Panel wyboru kształtu (_Shape Panel_)**:
  - Umożliwia wybór rodzaju kształtu, koloru obramowania oraz wypełnienia dla kształtu.

- **Suwaki i kontrolki**:
  - **Brightness slider (_Background Brightness_)**: Suwak do regulacji jasności tła.
  - **Opacity slider (_Middle layer opacity_)**: Suwak do regulacji przezroczystości warstwy środkowej.
  - **Animation speed spinner (_Animation Speed_)**: Kontrolka do regulacji szybkości animacji.

- **Informacje o bieżącej klatce**:
  - Wyświetla numer aktualnej klatki oraz całkowitą liczbę klatek.

#### Menu

Aplikacja zawiera również menu główne:

- **File**:
  - **New project (_New Project_)**: Rozpoczyna nowy projekt, resetując wszystkie zmiany.
  - **Save to file (_Save_)**: Zapisuje animację do pliku.
  - **Load from file (_Load_)**: Wczytuje animację z pliku.
  - **Exit (_Exit_)**: Zamyka aplikację.

- **Help**:
  - **About (_About_)**: Wyświetla podstawowe informacje o aplikacji.

#### Interakcja z użytkownikiem

Użytkownik może interagować z aplikacją poprzez klikanie na przyciski, przesuwanie suwaków, wybieranie opcji z menu oraz rysowanie na panelu rysunkowym. Aplikacja reaguje na te interakcje, aktualizując wyświetlane klatki animacji oraz informacje na panelach - odpowiednie metody _Refresh()_ oraz _Layout()_ wywoływane odpowiednio dla obiektów typu _MyPanel_ oraz _MainFrame_.

### Wyodrębnienie i zdefiniowanie zadań

#### Podział projektu na moduły
- **Interfejs użytkownika**:
  - Odpowiedzialny za wszystkie elementy interaktywne widoczne przez użytkownika.
  - Implementacja paneli, przycisków, suwaków, menu wraz z osługą zdarzeń.
- **Logika aplikacji**:
  - Zarządzanie animacją (dodawanie, usuwanie klatek, odtwarzanie).
  - Manipulacja obiektami na panelu (rysowanie, usuwanie, edycja kształtów)
  - Zarządzanie parametrami animacji (szybkość, jasność tła, przezroczystość warstwy)
- **Operacje na plikach**:
  - Zapisywanie i wczytywanie projektów animacji do/z pliku.
  - Zarządzanie obrazami tła.

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
