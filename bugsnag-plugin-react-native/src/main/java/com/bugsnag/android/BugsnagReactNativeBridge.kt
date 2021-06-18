package com.bugsnag.android

import com.bugsnag.android.StateEvent.AddMetadata
import com.bugsnag.android.StateEvent.ClearMetadataSection
import com.bugsnag.android.StateEvent.ClearMetadataValue
import com.bugsnag.android.StateEvent.UpdateContext
import com.bugsnag.android.StateEvent.UpdateUser
import com.bugsnag.android.internal.StateObserver

/**
 * Listens for changes in the user, context, and metadata, then informs the JS layer
 * of any state alterations.
 */
internal class BugsnagReactNativeBridge(
    private val client: Client,
    private val cb: (event: MessageEvent) -> Unit
) : StateObserver {

    override fun onStateChange(event: StateEvent) {
        val msgEvent: MessageEvent? = when (event) {
            is UpdateContext -> {
                MessageEvent("ContextUpdate", event.context)
            }
            is AddMetadata, is ClearMetadataSection, is ClearMetadataValue -> {
                MessageEvent("MetadataUpdate", client.metadata)
            }
            is UpdateUser -> {
                MessageEvent(
                    "UserUpdate",
                    mapOf(
                        Pair("id", event.user.id),
                        Pair("email", event.user.email),
                        Pair("name", event.user.name)
                    )
                )
            }
            else -> null
        }

        if (msgEvent != null) {
            cb(msgEvent)
        }
    }
}
