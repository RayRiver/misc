
return {
    class = "objects.monster",
    size = {
        width = 10,
        height = 10,
    },
    eyeshot = 200,
    components = {
        {
            class = "components.behavior_tree",
            config = {
                bt = "data.ai.bt_test_config",
                interval = 1,
            },
        },
    },
}
