# reservation-system

Toteuta ajanvarausjärjestelmä, jonka avulla voi varata tunnin mittaisia tapaamisaikoja. Kullekin tunnille voi varata vain yhden ajan. Järjestelmästä tulee voida myös perua tapaamisia, ja sen tulee pystyä tulostamaan tapaamiset ajankohdan mukaisessa järjestyksessä. Tapaaminen kuvataan yhdellä merkkijonolla, ja kuvauksessa pitää varautua ainakin 20 merkin pituisiin merkkijonoihin, mutta voit olettaa että kuvaus ei sisällä välimerkkiä. Kuvausmerkkijonon ei tarvitse olla uniikki. Ajanvarausjärjestelmä kattaa vain yhden vuoden tapaamiset, joten vuosiluvusta ei tarvitse pitää kirjaa.

## Ohjelmassa on seuraavat toiminnot:

* A kuvaus kuukausi päivä tunti: Lisää merkintä: Lisää merkinnän annetulla kuvauksella ajanvarausjärjestelmään. Tarkista että kuukausi, päivä ja tunti ovat järjellisiä. Voit kuitenkin päivän osalta olettaa (epärealistisesti), että kaikissa kuukausissa on sama määrä päiviä (enintään 31). Mikäli annettu ajankohta oli jo aiemmin varattu, toiminnosta tulee ilmoittaa virheilmoitus. Esim: A Hiustenleikkuu 3 26 14 varaa hiustenleikkuun 26.3. klo 14. (1 p)

* D kuukausi päivä tunti: Poista merkintä: Poistaa merkinnän annetulta ajankohdalta. Mikäli kyseisellä ajankohdalla ei ollut merkintää, tulostetaan virheilmoitus. Esim: D 3 26 14 poistaa edellä lisätyn merkinnän. (1 p)

* L : Tulosta kalenteri: Tulostaa kaikki sen hetkiset varaukset merkintäajan mukaisessa järjestyksessä: varhaisin merkintä ensimmäisenä ja myöhäisin viimeisenä. Kustakin merkinnästä tulee näkyä kuvaus sekä ajankohta seuraavassa formaatissa: kuvaus XX.YY. klo ZZ, jossa XX on päivä, YY kuukausi ja ZZ kellonaika. Tämä toiminto on kahden pisteen arvoinen siten että jos tulostus on muuten oikein mutta väärässä järjestyksessä, tulee yksi piste, ja jos järjestys on lisäksi oikea, tulee toinen piste.

* W tiedostonimi : Tallenna kalenteri: Tallentaa kaikki ajanvaraukset tiedostoon annetulla tiedostonnimellä (1 p)

* O tiedostonimi : Lataa kalenteri: Lataa kalenterin tiedostosta, korvaten muistissa mahdollisesti aiemmin olleen kanlenterin (1 p)

* Q : Poistu ohjelmasta: Poistuu ohjelmasta ja vapauttaa kaiken käytetyn muistin. Tämä toiminto on pakko toteuttaa, jotta havaitset mahdolliset muistivuodot.

Näiden lisäksi tietysti pitää olla toimiva main-funktio, joka kysyy käyttäjältä toistuvasti syötteitä ja toimii niiden mukaisesti.

Komennot alkavat siis yhdellä isolla kirjaimella ja sisältävät komennosta riippuen vaihtuvan määrän välilyönnillä eroteltuja parametreja. Alla esimerkki komentosarjasta:

```
A Hiustenleikkuu 3 26 14
A Ohjelmointiluento 3 27 12
A Ohjelmointilaskarit 3 27 14
A Matikanluento 3 26 14
D 3 26 14
A Matikanluento 3 26 14
L
W kalenteri
Q
```

Tämän seurauksena kalenteriin tulee kolme ensimmäistä tapahtumaa, mutta ensimmäinen Matikanluento-tapahtuma ei onnistu koska samalla paikalla on aiempi tapahtuma. Kun tämä on poistettu D-komennolla, matikanluennon lisääminen onnistuu. Lopuksi kalenteri tulostetaan ja tallennetaan levylle.

Saat suunnitella ohjelman kuten haluat, mutta noudata selkeää funktiorakennetta ja käytä asianmukaisia nimiä funktioissa ja muuttujissa, jotta ohjelmaa on helppo lukea. Voit hyödyntää korkeintaan yhtä .h - otsaketiedostoa (joka on nimettävä “projekti.h”) ja yhtä .c - tiedostoa. Otsaketiedostoa ei ole pakko käyttää, ja voit tehdä kaiken yhteen c - tiedostoonkin.

Muita yleisiä vaatimuksia ja ohjeita:

Testaamisen helpottamiseksi, edellä annettua komentoformaattia on noudatettava täsmällisesti.

Käytä dynaamista muistia säilön toteutukseen. Mielivaltaisen iso staattinen taulukko ei kelpaa. Dynaamisen muistin käytön tulee perustua varsinaiseen tilan tarpeeseen: malloc(1000000) ei ole hyväksyttävä ratkaisu.

Jokaisen komennon jälkeen on annettava tuloste, joka selkeästi kertoo onnistuiko toiminto vai ei.

Voit olettaa maksimipituuden käyttäjän syöteriville, kunhan se on riittävän pitkä. Esimerkiksi 80 merkkiä on riittävä.

Selkeästi virheellisten syötekomentojen jälkeen pitää antaa virheilmoitus, eikä ohjelma ainakaan saa kaatua. Voit kuitenkin olettaa että nimet ja vastaavat syötemerkkijonot eivät sisällä välimerkkejä (eli välimerkit toimivat pelkästään kenttien erottimena).

# main.c
```
#include "projekti.c"

int main()
{
    char filename[100];
    printf("To run the time reservation program interactively, press Enter.\n");
    printf("To run a file with commands, enter the name of the file (testing and debugging purposes): ");
    fgets(filename, 100, stdin);
    if (filename[0] == '\n') {
        printf("Welcome to the time reservation program!\n");
        run_program(stdin);
    } else {
        strtok(filename, "\n");
        FILE *fp = fopen(filename, "r");
        if (!fp)
        {
            printf("Error loading file %s.\n", filename);
            return 1;
        }
        run_program(fp);
        fclose(fp);
    }
    
    return 0;
}
```