
return {
    class = "NonPrioritySelectorNode",
    name = "priority node",
    precondition = {
        class = "PreconditionTRUE",
    },
    children = {
        {
            class = "bt.node_patrol",
            name = "patrol",
        },
        {
            class = "SequenceNode",
            name = "sequence node",
            children = {
                {
                    class = "ActionNode",
                    name = "test action 1",
                },
                {
                    class = "ActionNode",
                    name = "test action 3",
                },
                {
                    class = "ActionNode",
                    name = "test action 2",
                },
            },
        },
    },
}
