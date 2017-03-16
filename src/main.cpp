/** \file main.cpp
 * \brief
 * Pipeline modellezése és szimulálása merge rendezéssel.
 * A tesztesetek több vektor kombinációt próbálnak ki.
 *
 */
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "shell_task.hpp"

#include "my_gen_tasks.hpp"
#include "pipeline.hpp"

#include "memtrace.h"
/* later gtest */

#if defined(WIN32) || defined(_WIN32)
    #include <windows.h>
#endif

/// TESZT 1
void test_1() {
    std::cout << "Két rendezett vektor tesztelése, egyszintű összefésülés" << std::endl;
    PipeLine pipeline(new UserInput());
    pipeline.add_task(new Merger());
    pipeline.add_task(new UserOutput());
    pipeline.step_task();
}

/// TESZT 2
void test_2() {
    std::cout << "Négy rendezett vektor tesztelése, kétszintű összefésülés" << std::endl;
    PipeLine pipeline(new UserInput());
    pipeline.add_task(new Merger());
    pipeline.add_task(new Merger());
    pipeline.add_task(new UserOutput());
    pipeline.step_task();
}

/// TESZT 3
void test_3() {
    std::cout << "Nyolc rendezett vektor háromszintű összefésülése,\n\"tesztadatok.dat\" fájlból, \"eredmeny.txt\" fájlba" << std::endl;
    std::ifstream inputstream("tesztadatok.dat", std::ios::in);
    std::ofstream outputstream("test3_eredmeny.txt", std::ios::out);
    if (!inputstream.is_open())
        throw std::runtime_error("Nem sikerült megnyitni: \"tesztadatok.dat\"");
    if (!outputstream.is_open())
        throw std::runtime_error("Nem sikerült megnyitni: \"test3_eredmeny.dat\"");
    //Look like all good
    PipeLine pipeline(new UserInput(inputstream));
    pipeline.add_task(new Merger());
    pipeline.add_task(new Merger());
    pipeline.add_task(new Merger());
    pipeline.add_task(new UserOutput(outputstream));
    pipeline.step_task();
}

/// TESZT 4
void test_4() {
    std::cout << "Hiba generálása" << std::endl;
    PipeLine pipeline(new UserInput());
    pipeline.add_task(new Merger());
    pipeline.add_task(new UserOutput());
    pipeline.step_task();
}

/// Fõprogram a standard inputról olvas egy egész számot, majd
/// meghívja az annak megfelelõ tesztesetet.
/// A további bemenetet és kimenetet a tesztesetek kezelik.
int main() {
setlocale(LC_ALL, "");  // a rendszer környezeti változójában megadott nyelvi környezet beállítása
	#if defined(WIN32) || defined(_WIN32)
		SetConsoleCP(1250);
		SetConsoleOutputCP(1250);
	#endif
    try {
      int nr;
      std::cin >> nr;        // hanyadik teszteset
      std::cin.ignore(500, '\n'); // eldobunk max. 500 karaktert a sor végéig
      std::cout << std::endl << nr << ". teszteset:" << std::endl;
      switch (nr) {
        case 1:
            ///Két vektor összefésülése
            test_1();break;
        case 2:
            ///Négy vektor összefésülése
            test_2();break;
        case 3:
            ///Nyolc vektor összefésülése fájlból fájlba
            test_3();break;
        case 4:
            ///Hiba generálás
            test_4();break;
        default:
            std::cout << "Nics ilyen teszteset!" << std::endl;
      }
    // kivétel elkapása
    } catch (std::exception& e) {
        // kiírjuk, hogy milyen kivétel jött
        std::cerr << e.what() << std::endl;
    } catch (const char* str) {
        std::cerr << "Hiba:" << str <<std::endl;
    } catch (...) {
        std::cerr << "*** Ismeretlen hiba ****" << std::endl;
    }
	// itt minden memóriaterületnek, objektumnak fel kell szabadulnia, hogy a
    // memóriaszivárgás ellenõrizhetõ legyen!
    _CrtDumpMemoryLeaks();  // ellenõrzi, hogy volt-e memóriaszivárgás

}
