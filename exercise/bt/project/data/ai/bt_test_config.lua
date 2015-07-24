
return {
    class = "PrioritySelectorNode",
    name = "priority node",
    precondition = {
        class = "PreconditionTRUE",
    },
    children = {
        {
            class = "bt.node_attack",
            name = "attack",
            precondition = {
                class = "bt.cond_can_attack_target",
            },
        },
        {
            class = "bt.node_chevy",
            name = "chevy",
            precondition = {
                class = "bt.cond_found_target",
            },
        },
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
