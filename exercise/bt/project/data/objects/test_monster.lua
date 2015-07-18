
return {
    class = "objects.monster",
    eyeshot = 50,
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
