# Réflexion
Mémento à l'intérieur de l'espace d'édition d'une note.
Mémento à l'échelle globale de l'application ?


## Design pattern : utilisation

Usage possible des différents Design Patters conseillés.

### Decorator

#### Description
Le pattern Décorateur (Decorator) attache dynamiquement des responsabilités supplémentaires à un objet. Il fournit une alternative souple à l’héritage, pour étendre des fonctionnalités.

#### Utilisation
Probablement au niveau des notes


### factory

#### Description
Le design pattern Fabrique (Factory Method) définit une interface pour la création d'un objet en déléguant à ses sous-classes le choix des classes à instancier.

Permet de créer l'objet le mieux adapté à la sous classe.

#### Utilisation
Au niveau des notes : quels types de note est créée. => plus de flexibilité

### abstract factory

#### Description
Le pattern abstract Factory permet de rassembler des méthodes communes à des familles d’objets différents dans une classe commune : la fabrique abstraite, afin d’éviter au client d’appeler des méthodes différentes (concrètes) par famille d’objets.


#### Utilisation
Next level du design pattern précédent


### builder

#### Description
The builder pattern is an object creation software design pattern.

#### Utilisation
Builder often builds a Composite. Often, designs start out using Factory Method (less complicated, more customizable, subclasses proliferate) and evolve toward Abstract Factory, Prototype, or Builder (more flexible, more complex) as the designer discovers where more flexibility is needed. Sometimes creational patterns are complementary: Builder can use one of the other patterns to implement which components are built. Builders are good candidates for a fluent interface.



### bridge

#### Description
The bridge pattern is a design pattern used in software engineering that is meant to "decouple an abstraction from its implementation so that the two can vary independently", introduced by the Gang of Four (GoF).[1] The bridge uses encapsulation, aggregation, and can use inheritance to separate responsibilities into different classes.

#### Utilisation
Toujours plus de flexibilté


### composite
#### Description
En génie logiciel, un objet composite est un patron de conception (design pattern) structurel. Ce patron permet de concevoir une structure d'arbre, par exemple un arbre binaire en limitant à deux le nombre de sous-éléments.

#### Utilisation
Pour le stockage de notes ?

### iterator
#### Description
Pour le parcours des notes

#### Utilisation

### template method
#### Description
La technique du patron de méthode (template method pattern) est un patron de conception (design pattern) comportemental utilisé en génie logiciel.

Un patron de méthode définit le squelette d'un algorithme à l'aide d'opérations abstraites dont le comportement concret se trouvera dans les sous-classes, qui implémenteront ces opérations.

Cette technique, très répandue dans les classes abstraites, permet de :
fixer clairement des comportements standards qui devraient être partagés par toutes les sous-classes, même lorsque le détail des sous-opérations diffère ;

factoriser du code qui serait redondant s'il se trouvait répété dans chaque sous-classe.

#### Utilisation
Dans les différentes classes de notes


### adapter
#### Description
En génie logiciel, adaptateur (ou wrapper1) est un patron de conception (design pattern) de type structure (structural). Il permet de convertir l'interface d'une classe en une autre interface que le client attend.
#### Utilisation
Pour faire l'interfaçage avec l'interface. Plus facile pour l'évolutivité.


### visitor
#### Description
In object-oriented programming and software engineering, the visitor design pattern is a way of separating an algorithm from an object structure on which it operates

#### Utilisation

### strategy
#### Description
En génie logiciel, le patron stratégie est un patron de conception (design pattern) de type comportemental grâce auquel des algorithmes peuvent être sélectionnés à la volée au cours du temps d'exécution selon certaines conditions.

#### Utilisation
Dès lors qu'un objet peut effectuer plusieurs traitements différents, dépendant d'une variable ou d'un état.


### facade
#### Description
En génie logiciel, le patron de conception (ou design pattern) façade a pour but de cacher une conception et une interface complexe difficile à comprendre (cette complexité étant apparue « naturellement » avec l'évolution du sous-système en question).

#### Utilisation
Pour simplifier la structure

### memento IMPORTANT
#### Description
The memento pattern is a software design pattern that provides the ability to restore an object to its previous state (undo via rollback).

#### Utilisation
Obvious

Peut être à utiliser avec le Design Pattern Command
memento dans un iterator
