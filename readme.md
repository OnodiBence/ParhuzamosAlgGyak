# Párhuzamos algoritmusok 2024 II. félév beadandó feladat

## Szekvenciális vs párhuzamos

A program egy adott sorozatban keresi meg a leggyakoribb elemet. A szekvenciális verzió egymás után haladva számolja az elemek előfordulásait, majd meghatározza a leggyakoribb elemet. A párhuzamos verzió több szálon futtatja az elemek előfordulásainak számolását, és összegzi az eredményeket, majd meghatározza a leggyakoribb elemet.

### Specifikáció:

1.  **Bemenet:**

    - A számítógép által random generált sorozat.
    - A sorozat hossza.

2.  **Szekvenciális Verzió:**

    - Az elemeket egymás után számolja, és meghatározza a leggyakoribb elemet.
    - A kód egyetlen szálon fut, nincs párhuzamosítás.

3.  **Párhuzamos Verzió:**

    - A sorozatot több szálon dolgozza fel, és összegzi az elemek előfordulásait.
    - A szálak párhuzamosan futnak a processzormagokon, hogy felgyorsítsák a feldolgozást.
    - A párhuzamos verzióban szálak (pthreads) használatára van szükség.

4.  **Kimenet:**

    - A leggyakoribb elem.
    - Az elem előfordulásainak száma.

5.  **Tesztelés:**
    - A programot különböző méretű és tartalmú sorozatokkal kell tesztelni annak érdekében, hogy meggyőződjünk a helyes működésről.
    - Összehasonlítom a szekvenciális és párhuzamos verziók futási idejét és pontosságát.
