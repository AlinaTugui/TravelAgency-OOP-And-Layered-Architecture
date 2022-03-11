# TravelAgency-OOP-And-Layered-Architecture
Travel Agency App designed using OOP Principles and Qt framework.<br>
_I. Layered Architecture:_<br>
 - Domain<br>
 - Repository<br>
 - Service<br>
 - View (GUI)
 <br>
 
_II. Notable Design Patterns:_<br>
  - Observer Pattern (Changes inside ... class should be visible to all new application windows)<br>
  - Model-View-Controller (A class is responsible for getting the data from Repository and for passing it to the user depending on his request - prevents the preload of all entities at start)<br>
  - Command Design (Illustrated with Undo functionality, where I declared an abstract class ActiuneUndo(UndoAction) and 3 subclasses: UndoAdauga(UndoAdd), UndoModifica(UndoUpdate) and UndoSterge(UndoDelete))<br>
