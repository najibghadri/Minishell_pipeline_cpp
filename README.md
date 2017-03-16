# Generikus Pipeline modellezése

### Feladat
Tervezzen objektummodellt csővezeték (pipeline) feldolgozási architektúra mod-
ellezésére! A csővezeték-rendszerű feldolgozásban a feldolgozó egységek egymás
után vannak fűzve úgy, hogy a bemenetük a sorban megelőző elem kimenetére
van kapcsolva. A legegyszerűbb esetben minden feldolgozó egység bemenetén
van egy tároló, feldolgozás pedig két fázisban zajlik: Az első fázisban min-
den egység kiveszi a bemeneti tárolóból az ott levő adatot és feldolgozza, majd
a második fázisban az eredményt továbbadja a következő elem bemenetére.
Ezután a feldolgozási ciklus kezdődik elölről. Megj: A feldolgozó egységek
elvileg párhuzamosan működnek, de a tároló lehetőséget ad az egymás utáni
végrehajtásra is. Olyan modellt tervezzen, hogy tetszőleges hosszúságú csővezetéket
ki tudjunk alakı́tani, amin bármilyen (GENERIKUS) adat végighaladhat! Az
objektumok műveletvégző eleme legyen szintén definiálható! Mutassa be a
működést összefésülő rendezés (merge sort) csővezetékkel történő megvalósı́tásával!
Az összefűző rendezés lényege az, hogy önmagukban rendezett adathalmazokból
egyre nagyobb rendezett halmazokat képezünk. Csővezetékkel ez pl. úgy valósı́tható
meg, hogy a feldolgozó egységek bemenetére olyan halmazpárokat adunk, mely
halmazok önmagukban rendezettek, a kimeneten pedig ezek összefésült halmaza
jelenik meg. Pl:
5,7 — 1,8 – 1,2,3,8 – 1,2,3,4,5,6,7
4,6 — 2,3 – 4,5,6,7
(A halmazpárokat egymás alatt tüntettük fel, a – pedig a feldolgozó egységet
jelöli.) Válasszon megfelelő adatstruktúrát a rendezett halmazpárok tárolására!
Valósı́tsa meg a feldolgozó elemeket! Értelemszerűen 2 bemeneti adatból ka-
punk 1 kimeneti adatot, ı́gy a feladat elején ismertetett általános modellt ki kell
egészı́tenie úgy, hogy a feldolgozás ne mindig induljon el.
