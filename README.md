# So_Long

[![42 Project](https://img.shields.io/badge/42%20Project-so_long-blue?style=for-the-badge&logo=42)](https://github.com/vhacman/so_long)
[![C Language](https://img.shields.io/badge/Made%20with-C-00599C?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette Approved](https://img.shields.io/badge/Norminette-OK-brightgreen?style=for-the-badge)](https://github.com/42School/norminette)
[![Memory Leak Free](https://img.shields.io/badge/Leaks-Free-success?style=for-the-badge)](https://valgrind.org/)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Unix-violet?style=for-the-badge)]()
[![License](https://img.shields.io/badge/license-42%20Project-informational?style=for-the-badge)]()
[![Status](https://img.shields.io/badge/42%20status-Completed-brightgreen?style=for-the-badge)]()
[![Created](https://img.shields.io/badge/Created-Marzo_2025-blue?style=for-the-badge)]()

---

## 📚 Indice
- [Descrizione 📖](#descrizione-)
- [Requisiti 📦](#requisiti-)
- [Build](#build)
- [Esecuzione](#esecuzione)
- [Gameplay 🎮](#gameplay-)
- [Bonus 🧠](#bonus-)
- [Previw Mandatory](#preview_mandatory)
- [Previw Bonus](#preview_bonus)
- [Contatti 🧑‍💻](#contatti-)

--
## Descrizione 📖

**So Long** è un mini-gioco realizzato in C utilizzando la MiniLibX (MLX), parte del curriculum 42. L'obiettivo è guidare un personaggio su una mappa 2D, raccogliendo tutti gli oggetti (`C`) e raggiungendo l'uscita (`E`) evitando ostacoli (`1`) e nemici (`X`).

Il progetto prevede due versioni:
- **Mandatory**: logica base, rendering statico, validazioni mappa.
- **Bonus**: animazioni, nemico mobile, interfaccia migliorata, schermate dinamiche.

---
## Requisiti 📦

- OS: Linux (MLX non compatibile con Windows nativamente)
- Compilatore: `gcc`
- Librerie: `MiniLibX`, `X11`, `Xext`
- Strumenti utili: `valgrind`, `make`

---
 
## Build

```bash
make            # compila mandatory
make bonus      # compila bonus
make re         # ricompila da capo 
make clean      # rimuove i file oggetto (.o)
make fclean     # rimuove .o e binario
```
## Esecuzione:

```
./sp_long mappa.ber
```
---
## Gameplay 🎮
Mappa caricata da file .ber nella cartella src/maps/.

Controlli:
- W / ↑ : su
- S / ↓ : giù
- A / ← : sinistra
- D / → : destra
- ESC / tasto x : uscita

 Il giocatore deve raccogliere tutti i C per attivare l’uscita E.

---
## Bonus 🧠
La versione bonus include:

- Nemico che segue un percorso predefinito (pathfinding DFS).
- Collisione con il nemico = sconfitta.
- Animazione dei collectibles (C) su 4 frame.
- Schermate di intro, vittoria e sconfitta.
- Messaggio temporaneo se si tenta di uscire senza aver raccolto tutto.
- Conteggio mosse in sovraimpressione.

## Preview_mandatory

![Preview_mandatory](mandatory.gif)

## Contatti 🧑‍💻
[![LinkedIn](https://img.shields.io/badge/LinkedIn-blue?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/viorica-gabriela-hacman-63a412267/)
[![Facebook](https://img.shields.io/badge/Facebook-1877F2?style=for-the-badge&logo=facebook&logoColor=white)](https://www.facebook.com/profile.php?id=100090802467237)
[![Instagram](https://img.shields.io/badge/Instagram-E4405F?style=for-the-badge&logo=instagram&logoColor=white)](https://www.instagram.com/vgabrielah_/)

---
