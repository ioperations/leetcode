// #![feature(generic_associated_types)]
#![feature(type_alias_impl_trait)]
#![feature(generators, generator_trait)]
#![feature(slice_group_by)]
#![feature(test)]
#![cfg_attr(feature = "cargo-clippy", warn(clippy::pedantic))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_lossless))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_possible_truncation))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_possible_wrap))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_precision_loss))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_precision_loss))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_sign_loss))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::checked_conversions))]

#[cfg(test)]
use ctor::ctor;

#[cfg(test)]
use tracing_subscriber::{fmt, layer::SubscriberExt, util::SubscriberInitExt};

#[cfg(feature = "jaeger")]
#[cfg(test)]
#[ctor]
fn register_tracing() {
    use opentelemetry::global;
    // Allows you to pass along context (i.e., trace IDs) across services
    global::set_text_map_propagator(opentelemetry_jaeger::Propagator::new());
    // Sets up the machinery needed to export data to Jaeger
    // There are other OTel crates that provide pipelines for the vendors
    // mentioned earlier.
    let tracer = opentelemetry_jaeger::new_agent_pipeline()
        .with_service_name("leetcode.rs")
        .install_simple()
        .unwrap();

    // Create a tracing layer with the configured tracer
    let opentelemetry = tracing_opentelemetry::layer().with_tracer(tracer);

    // The SubscriberExt and SubscriberInitExt traits are needed to extend the
    // Registry to accept `opentelemetry (the OpenTelemetryLayer type).
    tracing_subscriber::registry()
        .with(opentelemetry)
        // Continue logging to stdout
        .with(fmt::Layer::default())
        .try_init()
        .unwrap();
}

#[cfg(not(feature = "jaeger"))]
#[cfg(test)]
#[ctor]
fn register_tracing() {
    tracing_subscriber::registry().with(fmt::layer()).init();
}

mod classic;

mod leetcode {
    automod::dir!("src/leetcode/");
}
