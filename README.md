# EmojAI

> [!IMPORTANT]
> This plugin has required no maintenance for years; the original
> Unreal Engine 4 code still works on Unreal Engine 5.5.
> Further engine versions are no longer monitored.

Born from a silly idea over at [Unreal Slackers](https://unrealslackers.org),
this plugin implements a widget component for Unreal Engine that lets you
display Behavior Tree states as emoji above your AI pawns:
![SK_Mannequin with a waving hand emoji above](Resources/hello.jpg)

Just mark the BT nodes that you're interested in with the
`EmojAI Display State` service and add the `EmojAI Display` component to
your pawn:
![Behavior tree and example output](Resources/behaviortree.png)

For everything else, the component comes with a C++ and Blueprint API:
![Blueprint example](Resources/blueprint.png)

The plugin works with arbitrary strings of course, but where's the fun in that?
Emoji characters turned out to be more useful than you'd initially think,
they're very compact.

Don't forget that you can bring up the built-in emoji selector of Windows by
pressing `Win+.` or `Win+;` in the Unreal Editor!
