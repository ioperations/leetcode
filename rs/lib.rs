// #![feature(generic_associated_types)]
#![feature(type_alias_impl_trait)]
#![feature(test)]
#![cfg_attr(feature = "clippy", warn(clippy::pedantic))]
#![cfg_attr(feature = "clippy", allow(clippy::cast_lossless))]
#![cfg_attr(feature = "clippy", allow(clippy::cast_possible_truncation))]
#![cfg_attr(feature = "clippy", allow(clippy::cast_possible_wrap))]
#![cfg_attr(feature = "clippy", allow(clippy::cast_precision_loss))]
#![cfg_attr(feature = "clippy", allow(clippy::cast_precision_loss))]
#![cfg_attr(feature = "clippy", allow(clippy::cast_sign_loss))]
#![cfg_attr(feature = "clippy", allow(clippy::checked_conversions))]

#[cfg(test)]
use ctor::ctor;

#[cfg(test)]
use tracing_subscriber::{fmt, layer::SubscriberExt, util::SubscriberInitExt};

#[cfg(feature = "jaeger")]
#[cfg(test)]
#[ctor]
fn register_tracing() {
    use opentelemetry::global;
    use tracing_chrome::ChromeLayerBuilder;

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

    let (chrome_layer, _guard) = ChromeLayerBuilder::new().build();

    let _ = std::thread::Builder::new()
        .name("tracing_chrome".to_string())
        .spawn(move || {
            std::thread::sleep(std::time::Duration::from_secs(10));
            drop(_guard);
        });

    // The SubscriberExt and SubscriberInitExt traits are needed to extend the
    // Registry to accept `opentelemetry (the OpenTelemetryLayer type).
    tracing_subscriber::registry()
        .with(opentelemetry)
        // Continue logging to stdout
        .with(chrome_layer)
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
    automod::dir!("rs/leetcode/");
}
