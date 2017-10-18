# tp4-sys

Ici, les philosophes ont décidé d'utiliser des fourchettes pour manger le repas.

Nous utilisons ici une structure qui contient le nombre de fourchettes (égal)
au nombre de philosophes, un tableau de booléan avec l'état de chaque fourchette
(true indique une fourchette libre, false indique qu'elle est prise).
Le mutex de cette structure permet d'empêcher un accès simultané à ses infos,
et la condition permet de mettre les philosophes en attente avant de prendre
leur fourchettes.

Le principe est qu'un philosophe ne peut prendre les fourchettes que par deux,
s'il ne peut pas alors il est mis en attente. Le problèmes est que deux
philosophes éloignés ne pourront pas prendre de fourchettes en même temps,
alors qu'ils ne prendront pas les mêmes; mais deux cotes à cote ne pourront
pas prendre une seule fourchette. Ce qui évitera donc les deadlocks.

Si une des fourchettes n'est pas libre, le philosophe n'en prend aucune, et
il est placé dans une file d'attente.

Les seuls tests que nous effectuons ici concernant l'état final des fourchettes
ce qui n'est peut-être pas vraiment utile.
