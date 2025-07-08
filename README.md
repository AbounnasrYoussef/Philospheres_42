📘 Philosophers – Projet 42 (mandatory)
Le projet Philosophers est une implémentation du célèbre problème des philosophes mangeurs (Dining Philosophers Problem) en C, visant à explorer les problématiques de concurrence, synchronisation des threads, et gestion des ressources partagées. Il fait partie du cursus mandatory de l'école 42.

🎯 Objectifs
  -  Implémenter une simulation où plusieurs philosophes mangent, dorment et pensent sans provoquer de conditions de compétition (race conditions) ni de deadlocks.

  -  Gérer efficacement l'accès concurrent aux fourchettes (ressources partagées) via des mutex.

  -  Respecter des contraintes de temps précises pour simuler le comportement des philosophes.

🛠️ Technologies utilisées
  -  Langage : C

  -  Bibliothèque : pthreads

  -  Compilation avec Makefile (norme 42)

🧠 Concepts clés

  -  Threads et synchronisation

  -  Mutex (pthread_mutex_t)

  -  Gestion du temps (gettimeofday, usleep)

  -  Protection des sections critiques

✅ Résultats attendus

  -  Aucun philosophe ne doit mourir prématurément (sauf si les règles le permettent).

  -  Pas de blocage mutuel (deadlock) entre les threads.

  -  Affichage précis et ordonné des actions (penser, manger, dormir).
