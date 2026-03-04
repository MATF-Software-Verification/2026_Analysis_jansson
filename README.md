# 2026_Analysis_jansson

**Autorka:** Marijana Čupovič
**Broj indeksa:** 1018/2025
**Kurs:** Verifikacija softvera

## Jansson

Projekat je rađen nad bibliotekom jansson koja služi za kodiranje, dekodiranje i manipulaciju JSON datotekama.

**Osnovne informacije:**
- *Repozitorijum:* https://github.com/akheron/jansson
- *Jezik:* C
- *Analizirana grana:* master
- *Heš komita:* ed5cae4

---

## Korišćeni alati i tehnike

| # | Alat | Kategorija  | Opis |
|---|------|-----------|------|
| 1 | clang-format | Formatiranje | Stilska provera |
| 2 | memcheck | Profajliranje | Rukovanje memorijom |
| 3 | lizard | Kompleksnost | Ciklomatska složenost |
| 4 | flawfind | Bezbednost | Sigurnosne ranjivosti |
| 5 | CUnit | Testiranje | Testiranje jedinica koda |
| 6 | CUnit | Testiranje | Integraciono testiranje |
| 7 | lcov  | Pokrivenost| Praćenje pokrivenosti testovma|

## Zaključci

Kod koji je analiziran je jako složen, ali su programerske prakse kreatora uredne i prate bezbednosna pravila. Nema curenja memorije, a rad sa rizičnim funkcijama je pedantno odrađen.