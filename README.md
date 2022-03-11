# TravelAgency-OOP-And-Layered-Architecture
Travel Agency App designed using OOP Principles and Qt framework.
I. Layered Architecture
  Domain
  Repository
  Service
  View (GUI)

II. Notable Design Patterns
  Observer Pattern (Changes inside ... class should be visible to all new application windows)
  Model-View-Controller (A class is responsible for getting the data from Repository and for passing it to the user depending on his request - prevents the preload of all entities at start)
  Command Design (Illustrated with Undo functionality, where I declared an abstract class ActiuneUndo(UndoAction) and 3 subclasses: UndoAdauga(UndoAdd), UndoModifica(UndoUpdate) and UndoSterge(UndoDelete))
