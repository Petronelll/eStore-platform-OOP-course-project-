<h1 align="center">
    eStore Platform
</h1>

***eStore Platform*** reprezinta un sistem pentru o platforma online dedicata vanzarii de produse diverse. 

Entitatile principale sunt **Produsele**, **Utilizatorii** si **Serverul** care stocheaza detalii despre produse si utilizatori si unde se pot efectua diverse operatii asupra entitatilor, precum căutări de produse, de utilizatori sau modificări de diferite cantități (adăugare sau scoatere de produse din coș).

***Cerinta temei*** este disponibila la urmatoarea adresa: [cerinta_tema](https://ocw.cs.pub.ro/courses/poo-is/tema2)

## Rezolvarea temei

##### Clase implementate:

* **Ierarhia Product**

  <img src="/pictures/producthierarchy.jpg" alt="product_hierarchy" style="zoom:60%;" />
  

* **Ierarhia User**
  

  <img src="/pictures/userhierarchy.png" alt="user_hierarchy" style="zoom:60%;" />

* Clasa ```ShoppingCart```

  Fiecare utilizator are asociat un cos de cumparaturi.

* Clasa ```Server```

  Clasa server este implementata folosind singleton pattern. Aici stocam toate datele legate de Useri si Produse (in liste neomogene).

* Clasa ```LRUCache```

  Aceasta clasa simuleaza comportamentul unui 'Least Recently Used Cache', care retine id-ul produselor ce reprezinta ultimele accesari ale utilizatorilor.

* Clasa ```QueuerySolver``` 

  In aceasta clasa am rezolvat o colectie de interogari. Acestea filtreaza cele doua liste din server pentru a gasit elementele care ne intereseaza.

## Prerequisites

- GCC compiler

## Checker si verificare

Pentru a rula checkerul se executa urmatorii pasi intr-un terminal:

- se executa comanda ```make``` pentru a compila si link-edita intregul proiectul. Implicit, asta inseamna generarea unui executabil numit ```eStore``` si a unor fisiere obiect.
- se executa scriptul de verificare folosind comanda ```./verificatorul.sh```

Checker-ul contine 3 foldere si script-ul de verificare. Cele 3 foldere sunt:

- ```data``` - contine toate informatiile ce ar putea fi procesate.
- ```out``` -  contine output-ul obtinut dupa rularea functiilor implementate.
- ```ref``` - Checker-ul verifica daca fisierele din 'out' se potrivesc cu cele din 'ref'. Daca da, testul va trece.
