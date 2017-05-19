# PenguinMeltdown
Simple arcade game with Unreal Engine

Hello friends!

Project folders architecture:
1) Assets - static and skeletal meshes, animations(including AnimBP), materials, textures(including UI).
2) Audio - all sounds and background music
3) Blueprints - all inherited from c++ classes objects, using for gameplay.
4) Experimental - testing features
5) Maps - all levels of game 
6) UI - all widgets
7) C++ classes - I think it's not necessary to explain

Game cycle:
1) Player controller uses PlayerPawn_Camera
2) PlayerPawn_Camera controlls PlayerPawn_Polar (originally it's done to manage several characters from under one pawn)
3) Before game started you need to create icelands with iceland generator and setup bound for generation new instances in game
4) Iceland generator and penguin generator creates new icelands and penguins on collision event in bound
5) Penguin generator creates new penguins with probability
5) Enemy generator creates new seals
6) Pickup generator create new pickups with random 
7) Polar need to take penguins one color and carry them to the safe zone 
8) Polar can die in the dead zone
9) Polar can to take pickup if will get close to it

You can see gameplay there: https://www.youtube.com/watch?v=Cqg7L0yQ2p8&t=146s. You can see a detailed description of the classes in the game through the tutorial (Content\Blueprints\Tutorials\GameInfo). Game controls you can see in info widget.

I hope it helps you in your projects or for your study. If you have any questions, please ask it. And I hope that you can forgive my English :) 

Best regards, your friend, Alex. 

Code and game architecture: Lipatov Alexey (https://www.youtube.com/channel/UCLpepxHXrspdwex1Krzj-MA)

2D Design,UI - Utina Anastasia (https://www.artstation.com/artist/ustya)

3D Artists - Shkarbanenko Kirill, Nuranov Vlad

Sound Design - Berezhnoy Gennady (https://soundcloud.com/igni5)
